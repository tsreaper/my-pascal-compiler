#ifndef MPC_AST_ARITH_H
#define MPC_AST_ARITH_H

#include "ast/val/ast_rval.h"

class ast_arith : public ast_rval {
public:
    ast_arith(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith() override;

    bool analyse(bool as_rval) override;

protected:
    ast_value_node *child_l, *child_r;

    bool semantics_child() override;

    bool semantics_self() override;

    virtual void do_arith() = 0;

    void arith_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

class ast_int_arith : public ast_arith {
public:
    ast_int_arith(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_int_arith() override = default;

protected:
    bool semantics_self() override;
};

#endif //MPC_AST_ARITH_H
