#ifndef MY_PASCAL_AST_BREAK_H
#define MY_PASCAL_AST_BREAK_H

#include "ast/ast_node.h"

class ast_break : public ast_node {
public:
    ~ast_break() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

    void codegen() override;
};

#endif //MY_PASCAL_AST_BREAK_H
