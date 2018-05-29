#ifndef MY_PASCAL_AST_CONT_H
#define MY_PASCAL_AST_CONT_H

#include "ast/ast_node.h"

class ast_cont : public ast_node {
public:
    ~ast_cont() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_CONT_H
