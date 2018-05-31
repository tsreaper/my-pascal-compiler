#ifndef MPC_AST_SYS_WRITE_H
#define MPC_AST_SYS_WRITE_H

#include "ast/ast_node.h"

class ast_sys_write : public ast_node {
public:
    explicit ast_sys_write(bool new_line);

    ~ast_sys_write() override;

    void add_param(ast_value_node *param);

    void explain_impl(std::string &res, int indent) const override;

private:
    bool new_line;
    std::vector<ast_value_node *> param_vec;

    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;
};

#endif //MPC_AST_SYS_WRITE_H
