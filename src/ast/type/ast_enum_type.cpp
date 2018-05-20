#include "env/type/env_enum_type.h"
#include "ast/type/ast_enum_type.h"

ast_enum_type::~ast_enum_type() {
    for (auto id : id_vec) {
        delete id;
    }
}

env_type ast_enum_type::get_type() const {
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
    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        if (!(*it)->analyse()) {
            return false;
        }
    }

    int enum_id = define_enum_type(id_vec);
    if (enum_id >= 0) {
        this->enum_id = enum_id;
        return true;
    } else {
        PRINT_ERROR_LINENO;
        return false;
    }
}

void ast_enum_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "enum_type(\n";

    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        (*it)->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}
