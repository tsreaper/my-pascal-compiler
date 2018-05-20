#ifndef MY_PASCAL_AST_LITERAL_H
#define MY_PASCAL_AST_LITERAL_H

#include "ast/ast_node.h"
#include "env/env_value.h"

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

#endif //MY_PASCAL_AST_LITERAL_H
