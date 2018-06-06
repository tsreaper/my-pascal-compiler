#include "sem/exp/sem_cmp.h"
#include "sem/type/sem_convert.h"
#include "gen/val/gen_literal.h"
#include "gen/type/gen_convert.h"
#include "gen/exp/gen_cmp.h"
#include "ast/exp/cmp/ast_cmp_ge.h"

ast_cmp_ge::ast_cmp_ge(ast_value_node *child_l, ast_value_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_ge::semantics_op() {
    if (!cmp_semantics_impl(true, true)) {
        return false;
    }

    if (child_l->get_value().known && child_r->get_value().known) {
        const sem_value &l_val = sem::sem_type_convert(child_l->get_type(), conv_type_l, child_l->get_value());
        const sem_value &r_val = sem::sem_type_convert(child_r->get_type(), conv_type_r, child_r->get_value());
        s_value = sem::do_cmp_ge(conv_type_l, conv_type_r, l_val, r_val);
    }
    return true;
}

void ast_cmp_ge::codegen() {
    if (s_value.known) {
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_cmp_ge(GEN_PARAMS);
    }
}

void ast_cmp_ge::explain_impl(std::string &res, int indent) const {
    binop_explain_impl("ge", res, indent);
}
