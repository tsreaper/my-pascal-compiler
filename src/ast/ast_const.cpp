#include "env/env_id.h"
#include "ast/ast_id.h"
#include "ast/ast_const.h"

ast_const_def::ast_const_def(ast_id *id, ast_value_node *value) : id(id), value(value) {}

ast_const_def::~ast_const_def() {
    delete id;
    delete value;
}

bool ast_const_def::analyse() {
    if (id->analyse() && value->analyse()) {
        if (register_const_id(id->get_id(), value->get_type(), value->get_value())) {
            return true;
        } else {
            PRINT_ERROR_LINENO;
            return false;
        }
    } else {
        return false;
    }
}

void ast_const_def::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "constant_definition(\n";

    id->explain_impl(res, indent + 1);
    value->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

ast_const_def_part::ast_const_def_part(
        ast_const_def *current_def, ast_node *next_def
) : current_def(current_def), next_def(next_def) {}

ast_const_def_part::~ast_const_def_part() {
    delete current_def;
    delete next_def;
}

bool ast_const_def_part::analyse() {
    return current_def->analyse() && next_def->analyse();
}

void ast_const_def_part::explain_impl(std::string &res, int indent) const {
    current_def->explain_impl(res, indent);
    next_def->explain_impl(res, indent);
}
