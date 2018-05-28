#ifndef MY_PASCAL_AST_FUNC_HEAD_H
#define MY_PASCAL_AST_FUNC_HEAD_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/val/ast_id.h"
#include "sem/func/sem_func.h"

class ast_func_head : public ast_node {
public:
    explicit ast_func_head(ast_id *id);

    ~ast_func_head() override;

    const std::string &get_name() const;

    int get_param_num() const;

    const std::vector<ast_id *> &get_param_name_node() const;

    const std::vector<ast_type_node *> &get_param_type_node() const;

    const sem_type &get_ret_type() const;

    const func_sign &get_func_sign() const;

    void add_param(ast_id *param_name, ast_type_node *param_type);

    void set_ret_type_node(ast_type_node *type);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_id *id;
    ast_type_node *type;
    std::vector<ast_id *> param_name_vec;
    std::vector<ast_type_node *> param_type_vec;
    func_sign sign;
    sem_type ret_type;
};

#endif //MY_PASCAL_AST_FUNC_HEAD_H
