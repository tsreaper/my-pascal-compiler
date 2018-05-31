#ifndef MPC_AST_REPEAT_H
#define MPC_AST_REPEAT_H

#include "ast/stmt/loop/ast_loop.h"

class ast_repeat : public ast_loop {
public:
    ast_repeat(ast_value_node *cond, ast_node *body);

    ~ast_repeat() override;

    llvm::BasicBlock *get_continue_block() const override;

    llvm::BasicBlock *get_break_block() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_value_node *cond;
    ast_node *body;

    llvm::BasicBlock *body_bb, *cond_bb, *cont_bb;

    bool semantics_body();

    bool semantics_cond();

    void codegen_before();

    void codegen_body();

    void codegen_cond();
};

#endif //MPC_AST_REPEAT_H
