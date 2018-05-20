#ifndef MY_PASCAL_AST_NODE_H
#define MY_PASCAL_AST_NODE_H

#include <string>
#include <env/env_type.h>

#include "ast/ast_interface.h"

#define PRINT_ERROR_LINENO fprintf(stderr, "(at %d:%d)\n", lineno, colno)

class ast_node {
public:
    virtual ~ast_node() = default;

    virtual bool analyse() = 0;

    void set_location(int lineno, int colno);

    void explain(std::string &res) const;

    virtual void explain_impl(std::string &res, int indent) const = 0;

protected:
    int lineno, colno;

    void explain_indent(std::string &res, int indent) const;
};

class ast_type_node : public ast_node, public ast_has_type {};

class ast_value_node : public ast_type_node, public ast_has_value {};

class ast_empty : public ast_node {
public:
    bool analyse() override;

    void explain_impl(std::string &, int) const override;
};

#endif //MY_PASCAL_AST_NODE_H
