#ifndef MY_PASCAL_AST_ASSIGN_H
#define MY_PASCAL_AST_ASSIGN_H

#include "ast/stmt/ast_stmt.h"
#include "ast/id/ast_id.h"

class ast_assign : public ast_stmt {
public:
    ast_assign(ast_id *id, ast_type_node *rhs);

    ~ast_assign() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_id *id;
    ast_type_node *rhs;

    llvm::Value *code_id;
    llvm::Value *code_rhs;
};

#endif //MY_PASCAL_AST_ASSIGN_H
