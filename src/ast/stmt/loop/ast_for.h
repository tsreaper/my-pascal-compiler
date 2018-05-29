#ifndef MY_PASCAL_AST_FOR_H
#define MY_PASCAL_AST_FOR_H

#include "ast/stmt/loop/ast_loop.h"
#include "ast/val/ast_id.h"

class ast_for : public ast_loop {
public:
    ast_for(ast_id *loop_id, ast_value_node *start_val, ast_value_node *end_val, ast_node *body, bool down);

    ~ast_for() override;

    llvm::BasicBlock *get_continue_block() const override;

    llvm::BasicBlock *get_break_block() const override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *loop_id;
    ast_value_node *start_val, *end_val;
    ast_node *body;
    bool down;

    llvm::BasicBlock *cond_bb, *body_bb, *step_bb, *cont_bb;

    bool semantics_range();

    bool semantics_body();

    void codegen_range();

    void codegen_body();
};

#endif //MY_PASCAL_AST_FOR_H
