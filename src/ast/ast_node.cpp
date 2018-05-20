#include "ast/ast_node.h"

void ast_node::set_location(int lineno, int colno) {
    this->lineno = lineno;
    this->colno = colno;
}

void ast_node::explain(std::string &res) const {
    explain_impl(res, 0);
}

void ast_node::explain_indent(std::string &res, int indent) const {
    for (int i = 0; i < indent * 4; i++) {
        res += ' ';
    }
}

bool ast_empty::analyse() {
    return true;
}

void ast_empty::explain_impl(std::string &, int) const {}
