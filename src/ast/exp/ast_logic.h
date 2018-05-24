#ifndef MY_PASCAL_AST_LOGIC_H
#define MY_PASCAL_AST_LOGIC_H

#include "ast/ast_node.h"

class ast_logic : public ast_type_node {
public:
    ast_logic(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_logic() override;

    const sem_type &get_type() const override;

    bool analyse() override;

protected:
    void logic_explain_impl(const std::string &op_name, std::string &res, int indent) const;

    ast_type_node *child_l, *child_r;
    sem_type type;
};

class ast_logic_and : public ast_logic {
public:
    ast_logic_and(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_logic_and() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_logic_or : public ast_logic {
public:
    ast_logic_or(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_logic_or() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_logic_xor : public ast_logic {
public:
    ast_logic_xor(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_logic_xor() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_logic_not : public ast_type_node {
public:
    explicit ast_logic_not(ast_type_node *child);

    ~ast_logic_not() override;

    const sem_type &get_type() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_type_node *child;
    sem_type type;
};

#endif //MY_PASCAL_AST_LOGIC_H
