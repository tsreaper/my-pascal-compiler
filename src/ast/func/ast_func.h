#ifndef MY_PASCAL_AST_FUNC_H
#define MY_PASCAL_AST_FUNC_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id.h"

class ast_func_dec : public ast_node {
public:
    explicit ast_func_dec(ast_id *name);

    ~ast_func_dec() override;

    int get_param_num() const;

    void add_param(ast_id* param_name, ast_type_node* param_type);

    void set_ret_type(ast_type_node *type);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *name;
    ast_type_node *type;
    std::vector<ast_id*> param_name_vec;
    std::vector<ast_type_node*> param_type_vec;
};

#endif //MY_PASCAL_AST_FUNC_H
