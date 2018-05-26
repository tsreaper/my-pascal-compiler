#ifndef MY_PASCAL_AST_CMP_H
#define MY_PASCAL_AST_CMP_H

#include "ast/ast_node.h"

class ast_cmp : public ast_type_node {
public:
    ast_cmp(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp() override;

    const sem_type &get_type() const override;

protected:
    ast_type_node *child_l, *child_r;
    sem_type type;

    llvm::Value *code_l, *code_r;

    bool semantics_child() override;

    bool cmp_semantics_impl(bool need_eq, bool need_cmp);

    void cmp_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

class ast_cmp_eq : public ast_cmp {
public:
    ast_cmp_eq(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_eq() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;
};

class ast_cmp_ne : public ast_cmp {
public:
    ast_cmp_ne(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_ne() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;
};

class ast_cmp_lt : public ast_cmp {
public:
    ast_cmp_lt(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_lt() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;
};

class ast_cmp_gt : public ast_cmp {
public:
    ast_cmp_gt(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_gt() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;
};

class ast_cmp_le : public ast_cmp {
public:
    ast_cmp_le(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_le() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;
};

class ast_cmp_ge : public ast_cmp {
public:
    ast_cmp_ge(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_cmp_ge() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;
};

#endif //MY_PASCAL_AST_CMP_H
