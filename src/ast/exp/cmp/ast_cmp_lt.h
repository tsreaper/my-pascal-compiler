#ifndef MPC_AST_CMP_LT_H
#define MPC_AST_CMP_LT_H

#include "ast/exp/cmp/ast_cmp.h"

class ast_cmp_lt : public ast_cmp {
public:
    ast_cmp_lt(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_cmp_lt() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_op() override;

    void codegen() override;
};

#endif //MPC_AST_CMP_LT_H
