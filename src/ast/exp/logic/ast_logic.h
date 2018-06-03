#ifndef MPC_AST_LOGIC_H
#define MPC_AST_LOGIC_H

#include "ast/val/ast_rval.h"

class ast_logic : public ast_value_node {
public:
    ast_logic(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_logic() override;

    bool analyse(bool as_rval) override;

protected:
    ast_value_node *child_l, *child_r;

    bool semantics_l();

    bool semantics_r();

    virtual void codegen_l() = 0;

    virtual void codegen_r() = 0;

    void logic_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

#endif //MPC_AST_LOGIC_H
