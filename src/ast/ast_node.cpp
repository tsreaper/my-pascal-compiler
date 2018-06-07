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

const sem_type &ast_type_node::get_type() const {
    return s_type;
}

const sem_value &ast_value_node::get_value() const {
    return s_value;
}

llvm::Value *ast_value_node::get_llvm_value() const {
    return llvm_value;
}

llvm::Value *ast_value_node::get_llvm_mem() const {
    if (llvm_mem != nullptr) {
        return llvm_mem;
    } else if (auto *llvm_inst = llvm::dyn_cast<llvm::LoadInst>(llvm_value)) {
        // We give memory support if the value is in memory
        return llvm_inst->getPointerOperand();
    } else {
        return nullptr;
    }
}

bool ast_value_node::analyse() {
    return analyse(true);
}

bool ast_value_node::analyse(bool as_rval) {
    if (semantics_child() && semantics_self()) {
        if (as_rval) {
            codegen();
        }
        return true;
    } else {
        return false;
    }
}
