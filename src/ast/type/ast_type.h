#ifndef MY_PASCAL_AST_TYPE_H
#define MY_PASCAL_AST_TYPE_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id.h"

class ast_type_def : public ast_node {
public:
    ast_type_def(ast_id* id, ast_type_node *type);

    ~ast_type_def() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    ast_type_node *type;
};

class ast_type_def_seq : public ast_node {
public:
    ~ast_type_def_seq() override;

    void add_type_def(ast_type_def *def);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    std::vector<ast_type_def*> type_def_vec;
};

#endif //MY_PASCAL_AST_TYPE_H
