#ifndef MY_PASCAL_AST_ARITH_DIV_FLOOR_H
#define MY_PASCAL_AST_ARITH_DIV_FLOOR_H

#include "ast/exp/arith/ast_arith.h"

class ast_arith_div_floor : public ast_int_arith {
public:
    ast_arith_div_floor(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith_div_floor() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void do_arith() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_ARITH_DIV_FLOOR_H
