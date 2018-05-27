#ifndef MY_PASCAL_AST_STMT_H
#define MY_PASCAL_AST_STMT_H

#include <vector>

#include "ast/ast_node.h"

class ast_stmt : public ast_node {};

class ast_stmt_seq : public ast_node {
public:
    ~ast_stmt_seq() override;

    void add_stmt(ast_stmt *stmt);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    std::vector<ast_stmt *> stmt_vec;
};

#endif //MY_PASCAL_AST_STMT_H
