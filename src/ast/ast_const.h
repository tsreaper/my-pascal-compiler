#ifndef MY_PASCAL_AST_CONST_H
#define MY_PASCAL_AST_CONST_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/ast_id.h"

class ast_const_def : public ast_node {
public:
    ast_const_def(ast_id *id, ast_value_node *value);

    ~ast_const_def() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    ast_value_node *value;
};

class ast_const_def_seq : public ast_node {
public:
    ~ast_const_def_seq() override;

    void add_const_def(ast_const_def *def);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    std::vector<ast_const_def*> const_def_vec;
};

#endif //MY_PASCAL_AST_CONST_H
