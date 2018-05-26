#ifndef MY_PASCAL_AST_ARITH_H
#define MY_PASCAL_AST_ARITH_H

#include "ast/ast_node.h"

class ast_arith : public ast_type_node {
public:
    ast_arith(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith() override;

    const sem_type &get_type() const override;

protected:
    ast_type_node *child_l, *child_r;
    sem_type type;

    llvm::Value *code_l, *code_r;

    bool semantics_child() override;

    bool semantics_self() override;

    void arith_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

class ast_arith_add : public ast_arith {
public:
    ast_arith_add(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith_add() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_arith_sub : public ast_arith {
public:
    ast_arith_sub(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith_sub() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_arith_mul : public ast_arith {
public:
    ast_arith_mul(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith_mul() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_arith_div : public ast_arith {
public:
    ast_arith_div(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith_div() override = default;

    bool semantics_self() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_arith_int_only : public ast_arith {
public:
    ast_arith_int_only(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith_int_only() override = default;

    bool semantics_self() override;
};

class ast_arith_div_floor : public ast_arith_int_only {
public:
    ast_arith_div_floor(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith_div_floor() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_arith_mod : public ast_arith_int_only {
public:
    ast_arith_mod(ast_type_node *child_l, ast_type_node *child_r);

    ~ast_arith_mod() override = default;

    void explain_impl(std::string &res, int indent) const override;
};

#endif //MY_PASCAL_AST_ARITH_H
