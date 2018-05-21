#ifndef MY_PASCAL_AST_VAR_H
#define MY_PASCAL_AST_VAR_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id.h"

class ast_var_dec : public ast_node {
public:
    explicit ast_var_dec(ast_type_node* type);

    ~ast_var_dec() override;

    void add_id(ast_id *id);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_type_node* type;
    std::vector<ast_id*> id_vec;
};

class ast_var_dec_seq : public ast_node {
public:
    ~ast_var_dec_seq() override;

    void add_var_dec(ast_var_dec *dec);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    std::vector<ast_var_dec*> var_dec_vec;
};

#endif //MY_PASCAL_AST_VAR_H
