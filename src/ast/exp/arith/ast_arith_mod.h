#ifndef MY_PASCAL_AST_ARITH_MOD_H
#define MY_PASCAL_AST_ARITH_MOD_H

#include "ast/exp/arith/ast_arith.h"

class ast_arith_mod : public ast_int_arith {
public:
    ast_arith_mod(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith_mod() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void do_arith() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_ARITH_MOD_H
