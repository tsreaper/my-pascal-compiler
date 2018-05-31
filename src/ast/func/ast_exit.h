#ifndef MPC_AST_EXIT_H
#define MPC_AST_EXIT_H

#include "ast/ast_node.h"

class ast_exit : public ast_node {
public:
    ~ast_exit() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void codegen() override;
};

#endif //MPC_AST_EXIT_H
