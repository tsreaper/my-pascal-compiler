#ifndef MPC_AST_CMP_H
#define MPC_AST_CMP_H

#include "ast/val/ast_rval.h"

class ast_cmp : public ast_rval {
public:
    ast_cmp(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_cmp() override;

    bool analyse(bool as_rval) override;

protected:
    ast_value_node *child_l, *child_r;

    bool semantics_child() override;

    bool cmp_semantics_impl(bool need_eq, bool need_cmp);

    virtual void do_cmp() = 0;

    void cmp_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

#endif //MPC_AST_CMP_H
