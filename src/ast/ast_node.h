#ifndef MY_PASCAL_AST_NODE_H
#define MY_PASCAL_AST_NODE_H

#include <string>

#include "ast/ast_interface.h"
#include "sem/type/sem_type.h"

#define PRINT_ERROR_MSG(e) fprintf(stderr, "%s (at %d:%d)\n", (e).what(), lineno, colno)

class ast_node {
public:
    virtual ~ast_node() = default;

    void set_location(int lineno, int colno);

    virtual bool analyse();

    void explain(std::string &res) const;

    virtual void explain_impl(std::string &res, int indent) const = 0;

protected:
    int lineno, colno;

    virtual bool semantics_child();

    virtual bool semantics_self();

    virtual void codegen();

    void explain_indent(std::string &res, int indent) const;
};

class ast_type_node : public ast_node, public ast_has_type {};

class ast_value_node : public ast_type_node, public ast_has_value {};

#endif //MY_PASCAL_AST_NODE_H
