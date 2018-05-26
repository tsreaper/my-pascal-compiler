#include "sem/exception/sem_exception.h"
#include "sem/type/sem_enum_type.h"
#include "ast/type/ast_enum_type.h"

ast_enum_type::ast_enum_type() {
    s_type = {false};
}

ast_enum_type::~ast_enum_type() {
    for (auto id : id_vec) {
        delete id;
    }
}

const sem_type &ast_enum_type::get_type() const {
    return s_type;
}

void ast_enum_type::add_id(ast_id *id) {
    id_vec.emplace_back(id);
}

bool ast_enum_type::semantics_child() {
    for (auto child : id_vec) {
        if (child->analyse() == nullptr) {
            return false;
        }
    }
    return true;
}

bool ast_enum_type::semantics_self() {
    try {
        enum_id = define_enum_type(id_vec);
        s_type = {true, meta_group::TYPE, type_group::ENUM, enum_id};
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_enum_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "enum_type(\n";

    for (auto child : id_vec) {
        child->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}
