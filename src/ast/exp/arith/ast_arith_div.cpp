#include "sem/exp/sem_arith.h"
#include "sem/type/sem_convert.h"
#include "sem/exception/sem_exception.h"
#include "gen/val/gen_literal.h"
#include "gen/type/gen_convert.h"
#include "gen/exp/gen_arith.h"
#include "ast/exp/arith/ast_arith_div.h"

ast_arith_div::ast_arith_div(ast_value_node *child_l, ast_value_node *child_r) : ast_binop(child_l, child_r) {}

bool ast_arith_div::semantics_op() {
    try {
        s_type = sem::assert_can_do_div(conv_type_l, conv_type_r);
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }

    if (child_l->get_value().known && child_r->get_value().known) {
        const sem_value &l_val = sem::sem_type_convert(child_l->get_type(), conv_type_l, child_l->get_value());
        const sem_value &r_val = sem::sem_type_convert(child_r->get_type(), conv_type_r, child_r->get_value());
        s_value = sem::do_arith_div(conv_type_l, conv_type_r, l_val, r_val);
    }
    return true;
}

void ast_arith_div::codegen() {
    if (s_value.known) {
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_arith_div(GEN_PARAMS_NO_TYPE);
    }
}

void ast_arith_div::explain_impl(std::string &res, int indent) const {
    binop_explain_impl("div", res, indent);
}
