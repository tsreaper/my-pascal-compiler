#ifndef MY_PASCAL_AST_LOGIC_AND_H
#define MY_PASCAL_AST_LOGIC_AND_H

#include "ast/exp/logic/ast_logic.h"

class ast_logic_and : public ast_logic {
public:
    ast_logic_and(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_logic_and() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void do_logic() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_LOGIC_AND_H
