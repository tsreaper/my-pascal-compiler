#ifndef MY_PASCAL_AST_CONST_H
#define MY_PASCAL_AST_CONST_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/ast_id.h"

class ast_const_def : public ast_node {
public:
    ast_const_def(ast_id *id, ast_value_node *value);

    ~ast_const_def() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    ast_value_node *value;
};

class ast_const_def_seq : public ast_node {
public:
    ~ast_const_def_seq() override;

    void add_const_def(ast_const_def *def);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    std::vector<ast_const_def*> const_def_vec;
};

// ======= literal =======

class ast_literal : public ast_value_node {};

class ast_lit_int : public ast_literal {
public:
    explicit ast_lit_int(int value);

    env_type get_type() const override;

    env_value get_value() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    int value;
};

class ast_lit_real : public ast_literal {
public:
    explicit ast_lit_real(double value);

    env_type get_type() const override;

    env_value get_value() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    double value;
};

class ast_lit_char : public ast_literal {
public:
    explicit ast_lit_char(char value);

    env_type get_type() const override;

    env_value get_value() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    char value;
};

class ast_lit_bool : public ast_literal {
public:
    explicit ast_lit_bool(bool value);

    env_type get_type() const override;

    env_value get_value() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    bool value;
};

class ast_lit_str : public ast_literal {
public:
    explicit ast_lit_str(const char *value);

    env_type get_type() const override;

    env_value get_value() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    std::string value;
};

#endif //MY_PASCAL_AST_CONST_H
