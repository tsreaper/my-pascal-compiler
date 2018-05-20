#ifndef MY_PASCAL_AST_NODE_H
#define MY_PASCAL_AST_NODE_H

#include <string>
#include <env/type.h>

class ast_node {
public:
    virtual ~ast_node() = default;

    virtual bool check() = 0;

    void explain(std::string &res);

    virtual void explain_impl(std::string &res, int indent) = 0;

protected:
    void explain_indent(std::string &res, int indent);
};

class ast_value_node : public ast_node {
public:
    virtual type value_type() = 0;
};

class ast_empty : public ast_node {
public:
    bool check() override;

    void explain_impl(std::string &, int) override;
};

#endif //MY_PASCAL_AST_NODE_H
