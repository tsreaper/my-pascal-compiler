#ifndef MPC_AST_ARITH_MUL_H
#define MPC_AST_ARITH_MUL_H

#include "ast/exp/arith/ast_arith.h"

class ast_arith_mul : public ast_arith {
public:
    ast_arith_mul(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith_mul() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void do_arith() override;

    void codegen() override;
};

#endif //MPC_AST_ARITH_MUL_H
