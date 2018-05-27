#ifndef MY_PASCAL_AST_CMP_H
#define MY_PASCAL_AST_CMP_H

#include "ast/ast_node.h"

class ast_cmp : public ast_value_node {
public:
    ast_cmp(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_cmp() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    bool analyse() override;

protected:
    ast_value_node *child_l, *child_r;
    sem_type s_type;
    sem_value s_value;

    bool semantics_child() override;

    bool cmp_semantics_impl(bool need_eq, bool need_cmp);

    virtual void do_cmp() = 0;

    void cmp_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

#endif //MY_PASCAL_AST_CMP_H
