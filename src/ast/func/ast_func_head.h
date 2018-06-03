#ifndef MPC_AST_FUNC_HEAD_H
#define MPC_AST_FUNC_HEAD_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id_seq_with_type.h"
#include "sem/func/sem_func.h"

class ast_func_head : public ast_node {
public:
    explicit ast_func_head(ast_id *id);

    ~ast_func_head() override;

    const std::string &get_name() const;

    int get_param_num() const;

    const std::vector<ast_id *> &get_param_name_node() const;

    const std::vector<sem_type> &get_param_type_node() const;

    const sem_type &get_ret_type() const;

    const func_sign &get_func_sign() const;

    void add_param(ast_id_seq_with_type *param);

    void set_ret_type_node(ast_type_node *type);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_id *id;
    ast_type_node *type;
    std::vector<ast_id_seq_with_type *> param_seq_vec;
    func_sign sign;
    sem_type ret_type;

    std::vector<ast_id *> param_name_vec;
    std::vector<sem_type> param_type_vec;
};

#endif //MPC_AST_FUNC_HEAD_H
