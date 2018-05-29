#ifndef MY_PASCAL_AST_IF_H
#define MY_PASCAL_AST_IF_H

#include "ast/ast_node.h"

class ast_if : public ast_node {
public:
    ast_if(ast_value_node *cond, ast_node *then_stmt, ast_node *else_stmt = nullptr);

    ~ast_if() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_value_node *cond;
    ast_node *then_stmt, *else_stmt;

    llvm::BasicBlock *then_bb, *else_bb, *cont_bb;

    bool semantics_cond();

    bool semantics_then();

    bool semantics_else();

    void codegen_cond();

    void codegen_then();

    void codegen_else();
};

#endif //MY_PASCAL_AST_IF_H
