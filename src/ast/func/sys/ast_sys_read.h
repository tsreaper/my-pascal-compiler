#ifndef MPC_AST_SYS_READ_H
#define MPC_AST_SYS_READ_H

#include "ast/ast_node.h"

class ast_sys_read : public ast_node {
public:
    ~ast_sys_read() override;

    void add_param(ast_value_node *param);

    void explain_impl(std::string &res, int indent) const override;

private:
    std::vector<ast_value_node *> param_vec;

    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;
};

#endif //MPC_AST_SYS_WRITE_H
