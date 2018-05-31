#ifndef MPC_AST_GOTO_H
#define MPC_AST_GOTO_H

#include "ast/ast_node.h"

class ast_goto : public ast_node {
public:
    explicit ast_goto(int label);

    ~ast_goto() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

    void codegen() override;

private:
    int label;
};

#endif //MPC_AST_GOTO_H
