#ifndef MPC_AST_EMPTY_STMT_H
#define MPC_AST_EMPTY_STMT_H

#include "ast/ast_node.h"

class ast_empty_stmt : public ast_node {
public:
    ~ast_empty_stmt() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

#endif //MPC_AST_EMPTY_STMT_H
