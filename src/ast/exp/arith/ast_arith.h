#ifndef MY_PASCAL_AST_ARITH_H
#define MY_PASCAL_AST_ARITH_H

#include "ast/ast_node.h"

class ast_arith : public ast_value_node {
public:
    ast_arith(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_arith() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    bool analyse() override;

protected:
    ast_value_node *child_l, *child_r;
    sem_type s_type;
    sem_value s_value;

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

#endif //MY_PASCAL_AST_ARITH_H
