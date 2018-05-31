#ifndef MPC_AST_STMT_H
#define MPC_AST_STMT_H

#include <vector>

#include "ast/ast_node.h"

class ast_stmt_seq : public ast_node {
public:
    ~ast_stmt_seq() override;

    void add_stmt(ast_node *stmt);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    std::vector<ast_node *> stmt_vec;
};

#endif //MPC_AST_STMT_H
