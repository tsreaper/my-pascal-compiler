#include "sem/exp/sem_logic.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_logic.h"
#include "ast/exp/logic/ast_logic_xor.h"

ast_logic_xor::ast_logic_xor(ast_value_node *child_l, ast_value_node *child_r) : ast_logic(child_l, child_r) {}

void ast_logic_xor::codegen_l() {}

void ast_logic_xor::codegen_r() {
    if (child_l->get_value().known && child_r->get_value().known) {
        s_value = sem::do_logic_xor(child_l->get_value(), child_r->get_value());
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_logic_xor(child_l->get_llvm_value(), child_r->get_llvm_value());
    }
}

void ast_logic_xor::explain_impl(std::string &res, int indent) const {
    binop_explain_impl("xor", res, indent);
}
