#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>

#include "codegen/codegen.h"
#include "ast/ast_node.h"

void ast_node::set_location(int lineno, int colno) {
    this->lineno = lineno;
    this->colno = colno;
}

llvm::Value *ast_node::analyse() {
    if (semantics_child() && semantics_self()) {
        return codegen();
    } else {
        return nullptr;
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

llvm::Value *ast_node::codegen() {
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm_context), 0);
}

void ast_node::explain_indent(std::string &res, int indent) const {
    for (int i = 0; i < indent * 4; i++) {
        res += ' ';
    }
}
