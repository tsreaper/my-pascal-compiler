#ifndef MPC_AST_CMP_GE_H
#define MPC_AST_CMP_GE_H

#include "ast/exp/cmp/ast_cmp.h"

class ast_cmp_ge : public ast_cmp {
public:
    ast_cmp_ge(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_cmp_ge() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

    void do_cmp() override;

    void codegen() override;
};

#endif //MPC_AST_CMP_GE_H
