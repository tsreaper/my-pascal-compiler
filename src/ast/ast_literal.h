#ifndef MY_PASCAL_AST_LITERAL_H
#define MY_PASCAL_AST_LITERAL_H

#include "ast_node.h"

class ast_int : public ast_value_node {
public:
    explicit ast_int(int value);

    type value_type() override;

    bool check() override;

    void explain_impl(std::string &res, int indent) override;

private:
    int value;
};

class ast_real : public ast_value_node {
public:
    explicit ast_real(double value);

    type value_type() override;

    bool check() override;

    void explain_impl(std::string &res, int indent) override;

private:
    double value;
};

class ast_str : public ast_value_node {
public:
    explicit ast_str(const char *value);

    type value_type() override;

    bool check() override;

    void explain_impl(std::string &res, int indent) override;

private:
    std::string value;
};

#endif //MY_PASCAL_AST_LITERAL_H
