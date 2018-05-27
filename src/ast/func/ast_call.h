#ifndef MY_PASCAL_AST_CALL_H
#define MY_PASCAL_AST_CALL_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/val/ast_id.h"
#include "sem/func/sem_func.h"

class ast_call : public ast_value_node {
public:
    explicit ast_call(ast_id *id);

    ~ast_call() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    void add_param(ast_type_node *param);

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    std::vector<ast_type_node *> param_vec;
    sem_type s_type;
    sem_value s_value;
    func_sign sign;

    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_CALL_H
