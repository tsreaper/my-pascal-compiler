#include "sem/exp/sem_arith.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_arith.h"
#include "ast/exp/arith/ast_arith_mod.h"

ast_arith_mod::ast_arith_mod(
        ast_value_node *child_l, ast_value_node *child_r
) : ast_int_arith(child_l, child_r) {}

void ast_arith_mod::do_arith() {
    s_value = sem::do_arith_mod(child_l->get_value(), child_r->get_value());
}

void ast_arith_mod::codegen() {
    if (s_value.known) {
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_arith_mod(child_l->get_llvm_value(), child_r->get_llvm_value());
    }
}

void ast_arith_mod::explain_impl(std::string &res, int indent) const {
    arith_explain_impl("mod", res, indent);
}
