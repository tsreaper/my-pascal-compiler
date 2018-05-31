#ifndef MPC_AST_LOGIC_H
#define MPC_AST_LOGIC_H

#include "ast/ast_node.h"

class ast_logic : public ast_value_node {
public:
    ast_logic(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_logic() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    bool analyse() override;

protected:
    ast_value_node *child_l, *child_r;
    sem_type s_type;
    sem_value s_value;

    bool semantics_child() override;

    bool semantics_self() override;

    virtual void do_logic() = 0;

    void logic_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

#endif //MPC_AST_LOGIC_H
