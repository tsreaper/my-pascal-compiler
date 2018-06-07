#ifndef MPC_AST_EXIT_H
#define MPC_AST_EXIT_H

#include "ast/ast_node.h"

class ast_exit : public ast_node {
public:
    explicit ast_exit(ast_value_node *ret_val = nullptr);

    ~ast_exit() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *ret_val;

    sem_type ret_type;
};

#endif //MPC_AST_EXIT_H
