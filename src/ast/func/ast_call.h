#ifndef MY_PASCAL_AST_CALL_H
#define MY_PASCAL_AST_CALL_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id.h"
#include "sem/func/sem_func.h"

class ast_call : public ast_type_node {
public:
    explicit ast_call(ast_id *id);

    ~ast_call() override;

    const sem_type &get_type() const override;

    void add_param(ast_type_node *param);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    std::vector<ast_type_node *> param_vec;
    sem_type type;
    func_sign sign;
};

#endif //MY_PASCAL_AST_CALL_H
