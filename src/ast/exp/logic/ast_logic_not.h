#ifndef MY_PASCAL_AST_LOGIC_NOT_H
#define MY_PASCAL_AST_LOGIC_NOT_H

#include "ast/ast_node.h"

class ast_logic_not : public ast_value_node {
public:
    explicit ast_logic_not(ast_value_node *child);

    ~ast_logic_not() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void codegen() override;

private:
    ast_value_node *child;
    sem_type s_type;
    sem_value s_value;

    bool semantics_child() override;

    bool semantics_self() override;

    void do_logic();
};

#endif //MY_PASCAL_AST_LOGIC_NOT_H
