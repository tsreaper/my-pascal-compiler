#ifndef MPC_AST_LOGIC_H
#define MPC_AST_LOGIC_H

#include "ast/exp/ast_binop.h"

class ast_logic : public ast_binop {
public:
    ast_logic(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_logic() override = default;

    bool analyse(bool as_rval) override;

protected:
    bool semantics_l();

    bool semantics_r();

    virtual void codegen_l() = 0;

    virtual void codegen_r() = 0;
};

#endif //MPC_AST_LOGIC_H
