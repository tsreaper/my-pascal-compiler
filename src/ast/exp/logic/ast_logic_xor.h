#ifndef MPC_AST_LOGIC_XOR_H
#define MPC_AST_LOGIC_XOR_H

#include "ast/exp/logic/ast_logic.h"

class ast_logic_xor : public ast_logic {
public:
    ast_logic_xor(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_logic_xor() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void codegen_l() override;

    void codegen_r() override;
};

#endif //MPC_AST_LOGIC_XOR_H
