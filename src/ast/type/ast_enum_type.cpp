#include "sem/exception/sem_exception.h"
#include "sem/type/sem_enum_type.h"
#include "ast/type/ast_enum_type.h"

ast_enum_type::~ast_enum_type() {
    for (auto id : id_vec) {
        delete id;
    }
}

sem_type ast_enum_type::get_type() const {
    if (enum_id >= 0) {
        return {true, meta_group::TYPE, type_group::ENUM, enum_id};
    } else {
        return {false};
    }
}

void ast_enum_type::add_id(ast_id *id) {
    id_vec.emplace_back(id);
}

bool ast_enum_type::analyse() {
    for (auto child : id_vec) {
        if (!child->analyse()) {
            return false;
        }
    }

    try {
        enum_id = define_enum_type(id_vec);
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
