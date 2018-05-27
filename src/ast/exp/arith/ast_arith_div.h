#ifndef MY_PASCAL_AST_ARITH_DIV_H
#define MY_PASCAL_AST_ARITH_DIV_H

#include "ast/exp/arith/ast_arith.h"

class ast_arith_div : public ast_arith {
public:
    ast_arith_div(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith_div() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

    void do_arith() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_ARITH_DIV_H
