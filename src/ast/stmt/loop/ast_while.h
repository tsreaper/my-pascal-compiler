#ifndef MPC_AST_WHILE_H
#define MPC_AST_WHILE_H

#include "ast/stmt/loop/ast_loop.h"

class ast_while : public ast_loop {
public:
    ast_while(ast_value_node *cond, ast_node *body);

    ~ast_while() override;

    llvm::BasicBlock *get_continue_block() const override;

    llvm::BasicBlock *get_break_block() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_value_node *cond;
    ast_node *body;

    llvm::BasicBlock *cond_bb, *body_bb, *cont_bb;

    bool semantics_cond();

    bool semantics_body();

    void codegen_before();

    void codegen_cond();

    void codegen_body();
};

#endif //MPC_AST_WHILE_H
