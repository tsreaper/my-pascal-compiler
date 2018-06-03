#ifndef MPC_AST_ARRAY_IDX_H
#define MPC_AST_ARRAY_IDX_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/exp/ast_exp_seq.h"

class ast_array_idx : public ast_value_node {
public:
    ast_array_idx(ast_value_node *arr, ast_exp_seq *idx_seq);

    ~ast_array_idx() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *arr;
    ast_exp_seq *idx_seq;
};

#endif //MPC_AST_ARRAY_IDX_H
