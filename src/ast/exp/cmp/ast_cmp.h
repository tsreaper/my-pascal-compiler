#ifndef MPC_AST_CMP_H
#define MPC_AST_CMP_H

#include "ast/exp/ast_binop.h"

class ast_cmp : public ast_binop {
public:
    ast_cmp(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_cmp() override = default;

protected:
    bool cmp_semantics_impl(bool need_eq, bool need_cmp);
};

#endif //MPC_AST_CMP_H
