#ifndef MPC_AST_FOR_H
#define MPC_AST_FOR_H

#include "ast/ast_node.h"
#include "ast/stmt/loop/ast_loop.h"

class ast_for : public ast_loop {
public:
    ast_for(ast_value_node *lhs, ast_value_node *start_val, ast_value_node *end_val, ast_node *body, bool down);

    ~ast_for() override;

    llvm::BasicBlock *get_continue_block() const override;

    llvm::BasicBlock *get_break_block() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_value_node *lhs;
    ast_value_node *start_val, *end_val;
    ast_node *body;
    bool down;

    llvm::BasicBlock *cond_bb, *body_bb, *step_bb, *cont_bb;

    bool semantics_range();

    bool semantics_body();

    void codegen_range();

    void codegen_body();
};

#endif //MPC_AST_FOR_H
