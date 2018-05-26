#ifndef MY_PASCAL_AST_LITERAL_H
#define MY_PASCAL_AST_LITERAL_H

#include "ast/ast_node.h"
#include "sem/type/sem_type.h"
#include "sem/value/sem_value.h"

class ast_literal : public ast_value_node {
public:
    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

protected:
    sem_type s_type;
    sem_value s_value;
};

class ast_lit_int : public ast_literal {
public:
    explicit ast_lit_int(int value);

    void explain_impl(std::string &res, int indent) const override;

private:
    int value;
};

class ast_lit_real : public ast_literal {
public:
    explicit ast_lit_real(double value);

    void explain_impl(std::string &res, int indent) const override;

private:
    double value;
};

class ast_lit_char : public ast_literal {
public:
    explicit ast_lit_char(char value);

    void explain_impl(std::string &res, int indent) const override;

private:
    char value;
};

class ast_lit_bool : public ast_literal {
public:
    explicit ast_lit_bool(bool value);

    void explain_impl(std::string &res, int indent) const override;

private:
    bool value;
};

class ast_lit_str : public ast_literal {
public:
    explicit ast_lit_str(const char *value);

    void explain_impl(std::string &res, int indent) const override;

private:
    std::string value;
};

#endif //MY_PASCAL_AST_LITERAL_H
