#include "ast/ast_node.h"

void ast_node::explain(std::string &res) {
    explain_impl(res, 0);
}

void ast_node::explain_indent(std::string &res, int indent) {
    for (int i = 0; i < indent * 4; i++) {
        res += ' ';
    }
}

bool ast_empty::check() {
    return true;
}

void ast_empty::explain_impl(std::string &, int) {}