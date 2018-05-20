#include "ast_const.h"

ast_const_def::ast_const_def(ast_id *id, ast_value_node *value) : id(id), value(value) {}

ast_const_def::~ast_const_def() {
    delete id;
    delete value;
}

bool ast_const_def::check() {
    return true;
}

void ast_const_def::explain_impl(std::string &res, int indent) {
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

bool ast_const_def_part::check() {
    return current_def->check() && next_def->check();
}

void ast_const_def_part::explain_impl(std::string &res, int indent) {
    current_def->explain_impl(res, indent);
    next_def->explain_impl(res, indent);
}
