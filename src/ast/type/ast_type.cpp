#include "env/type/env_type.h"
#include "ast/type/ast_type.h"

ast_type_def::ast_type_def(ast_id *id, ast_type_node *type) : id(id), type(type) {}

ast_type_def::~ast_type_def() {
    delete id;
    delete type;
}

bool ast_type_def::analyse() {
    if (id->analyse() && type->analyse()) {
        if (define_type_id(id->get_id(), type->get_type())) {
            return true;
        } else {
            PRINT_ERROR_LINENO;
            return false;
        }
    } else {
        return false;
    }
}

void ast_type_def::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "type_definition(\n";

    id->explain_impl(res, indent + 1);
    type->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

ast_type_def_seq::~ast_type_def_seq() {
    for (auto child : type_def_vec) {
        delete child;
    }
}

void ast_type_def_seq::add_type_def(ast_type_def *def) {
    type_def_vec.emplace_back(def);
}

bool ast_type_def_seq::analyse() {
    for (auto child : type_def_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_type_def_seq::explain_impl(std::string &res, int indent) const {
    for (auto child : type_def_vec) {
        child->explain_impl(res, indent);
    }
}
