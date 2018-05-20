#ifndef MY_PASCAL_AST_PASCAL_H
#define MY_PASCAL_AST_PASCAL_H

#include "ast/ast_node.h"

class ast_pascal : public ast_node {
public:
    ast_pascal(
            ast_node *label_dec_part, ast_node *const_def_part, ast_node *type_def_part,
            ast_node *var_dec_part, ast_node *proc_func_dec_part, ast_node *compound_stm
    );

    ~ast_pascal() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_node *label_dec_part;
    ast_node *const_def_part;
    ast_node *type_def_part;
    ast_node *var_dec_part;
    ast_node *proc_func_dec_part;
    ast_node *compound_stm;
};

#endif //MY_PASCAL_AST_PASCAL_H
