#include "sem/exp/sem_cmp.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_cmp.h"
#include "ast/exp/cmp/ast_cmp_le.h"

ast_cmp_le::ast_cmp_le(ast_value_node *child_l, ast_value_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_le::semantics_self() {
    return cmp_semantics_impl(true, true);
}

void ast_cmp_le::do_cmp() {
    s_value = sem::do_cmp_le(child_l->get_type(), child_r->get_type(), child_l->get_value(), child_r->get_value());
}

void ast_cmp_le::codegen() {
    if (s_value.known) {
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_cmp_le(
                child_l->get_type(), child_r->get_type(), child_l->get_llvm_value(), child_r->get_llvm_value()
        );
    }
}

void ast_cmp_le::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("less_than_or_equal", res, indent);
}
