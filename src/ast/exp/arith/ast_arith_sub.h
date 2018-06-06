#ifndef MPC_AST_ARITH_SUB_H
#define MPC_AST_ARITH_SUB_H

#include "ast/exp/ast_binop.h"

class ast_arith_sub : public ast_binop {
public:
    ast_arith_sub(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith_sub() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_op() override;

    void codegen() override;
};

#endif //MPC_AST_ARITH_SUB_H
