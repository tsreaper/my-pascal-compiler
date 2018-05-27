#ifndef MY_PASCAL_AST_LOGIC_OR_H
#define MY_PASCAL_AST_LOGIC_OR_H

#include "ast/exp/logic/ast_logic.h"

class ast_logic_or : public ast_logic {
public:
    ast_logic_or(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_logic_or() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void do_logic() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_LOGIC_OR_H
