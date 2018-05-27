#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "ast/ast_node.h"

void ast_node::set_location(int lineno, int colno) {
    this->lineno = lineno;
    this->colno = colno;
}

bool ast_node::analyse() {
    if (semantics_child() && semantics_self()) {
        codegen();
        return true;
    } else {
        return false;
    }
}

void ast_node::explain(std::string &res) const {
    explain_impl(res, 0);
}

bool ast_node::semantics_child() {
    return true;
}

bool ast_node::semantics_self() {
    return true;
}

void ast_node::codegen() {}

void ast_node::explain_indent(std::string &res, int indent) const {
    for (int i = 0; i < indent * 4; i++) {
        res += ' ';
    }
}
