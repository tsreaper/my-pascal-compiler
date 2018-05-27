#include "sem/exp/sem_cmp.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_cmp.h"
#include "ast/exp/cmp/ast_cmp_ge.h"

ast_cmp_ge::ast_cmp_ge(ast_value_node *child_l, ast_value_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_ge::semantics_self() {
    return cmp_semantics_impl(true, true);
}

void ast_cmp_ge::do_cmp() {
    s_value = sem::do_cmp_ge(child_l->get_type(), child_r->get_type(), child_l->get_value(), child_r->get_value());
}

void ast_cmp_ge::codegen() {
    if (s_value.known) {
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_cmp_ge(
                child_l->get_type(), child_r->get_type(), child_l->get_llvm_value(), child_r->get_llvm_value()
        );
    }
}

void ast_cmp_ge::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("greater_than_or_equal", res, indent);
}
