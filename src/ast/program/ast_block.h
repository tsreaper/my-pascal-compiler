#ifndef MY_PASCAL_AST_BLOCK_H
#define MY_PASCAL_AST_BLOCK_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/stmt/ast_stmt.h"

class ast_block_head : public ast_node {
public:
    ~ast_block_head() override;

    void add_node(ast_node *node);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    std::vector<ast_node *> node_vec;
};

class ast_block : public ast_node {
public:
    ast_block(ast_block_head *head, ast_stmt_seq *body);

    ~ast_block() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    ast_block_head *head;
    ast_stmt_seq *body;
};

#endif //MY_PASCAL_AST_BLOCK_H
