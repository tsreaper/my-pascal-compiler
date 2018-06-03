#ifndef MPC_AST_LOGIC_NOT_H
#define MPC_AST_LOGIC_NOT_H

#include "ast/val/ast_rval.h"

class ast_logic_not : public ast_rval {
public:
    explicit ast_logic_not(ast_value_node *child);

    ~ast_logic_not() override;

    bool analyse(bool as_rval) override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *child;

    void do_logic();
};

#endif //MPC_AST_LOGIC_NOT_H
