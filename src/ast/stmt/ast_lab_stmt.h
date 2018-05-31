#ifndef MPC_AST_LAB_STMT_H
#define MPC_AST_LAB_STMT_H

#include "ast/ast_node.h"

class ast_lab_stmt : public ast_node {
public:
    ast_lab_stmt(int label, ast_node* stmt);

    ~ast_lab_stmt() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    int label;
    ast_node* stmt;
};

#endif //MPC_AST_LAB_STMT_H
