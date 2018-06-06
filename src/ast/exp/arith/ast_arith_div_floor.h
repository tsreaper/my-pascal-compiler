#ifndef MPC_AST_ARITH_DIV_FLOOR_H
#define MPC_AST_ARITH_DIV_FLOOR_H

#include "ast/exp/ast_binop.h"

class ast_arith_div_floor : public ast_binop {
public:
    ast_arith_div_floor(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith_div_floor() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_op() override;

    void codegen() override;
};

#endif //MPC_AST_ARITH_DIV_FLOOR_H
