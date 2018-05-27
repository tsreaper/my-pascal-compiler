#ifndef MY_PASCAL_AST_CMP_GT_H
#define MY_PASCAL_AST_CMP_GT_H

#include "ast/exp/cmp/ast_cmp.h"

class ast_cmp_gt : public ast_cmp {
public:
    ast_cmp_gt(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_cmp_gt() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

    void do_cmp() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_CMP_GT_H
