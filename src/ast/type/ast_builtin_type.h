#ifndef MY_PASCAL_AST_BUILTIN_TYPE_H
#define MY_PASCAL_AST_BUILTIN_TYPE_H

#include "ast/ast_node.h"
#include "sem/type/sem_type.h"
#include "sem/value/sem_value.h"

class ast_builtin_type : public ast_type_node {};

class ast_bti_int : public ast_builtin_type {
public:
    sem_type get_type() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_bti_real : public ast_builtin_type {
public:
    sem_type get_type() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_bti_char : public ast_builtin_type {
public:
    sem_type get_type() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_bti_bool : public ast_builtin_type {
public:
    sem_type get_type() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

class ast_bti_str : public ast_builtin_type {
public:
    sem_type get_type() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;
};

#endif //MY_PASCAL_AST_BUILTIN_TYPE_H
