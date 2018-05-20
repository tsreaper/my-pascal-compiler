#ifndef MY_PASCAL_AST_NODE_H
#define MY_PASCAL_AST_NODE_H

#include <string>
#include <env/env_type.h>

#include "ast/ast_interface.h"

class ast_node {
public:
    virtual ~ast_node() = default;

    virtual bool analyse() = 0;

    void explain(std::string &res) const;

    virtual void explain_impl(std::string &res, int indent) const = 0;

protected:
    void explain_indent(std::string &res, int indent) const;
};

class ast_value_node : public ast_node, public ast_has_value, public ast_has_type {};

class ast_empty : public ast_node {
public:
    bool analyse() override;

    void explain_impl(std::string &, int) const override;
};

#endif //MY_PASCAL_AST_NODE_H
