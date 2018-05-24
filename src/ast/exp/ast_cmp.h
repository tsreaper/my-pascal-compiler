#ifndef MY_PASCAL_AST_CMP_H
#define MY_PASCAL_AST_CMP_H

#include "ast/ast_node.h"

class ast_cmp : public ast_type_node {
public:
    ast_cmp(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp() override;

    const sem_type &get_type() const override;

protected:
    bool cmp_analyse_impl(bool need_eq, bool need_cmp);

    void cmp_explain_impl(const std::string &op_name, std::string &res, int indent) const;

    ast_type_node *child_l, *child_r;
    sem_type type;
};

class ast_cmp_eq : public ast_cmp {
public:
    ast_cmp_eq(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_eq() override = default;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_cmp_ne : public ast_cmp {
public:
    ast_cmp_ne(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_ne() override = default;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_cmp_lt : public ast_cmp {
public:
    ast_cmp_lt(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_lt() override = default;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_cmp_gt : public ast_cmp {
public:
    ast_cmp_gt(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_gt() override = default;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_cmp_le : public ast_cmp {
public:
    ast_cmp_le(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_le() override = default;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_cmp_ge : public ast_cmp {
public:
    ast_cmp_ge(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_ge() override = default;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

#endif //MY_PASCAL_AST_CMP_H
