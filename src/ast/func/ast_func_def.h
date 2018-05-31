#ifndef MPC_AST_FUNC_DEF_H
#define MPC_AST_FUNC_DEF_H

#include "ast/func/ast_func_head.h"
#include "ast/program/ast_block.h"

class ast_func_def : public ast_node {
public:
    ast_func_def(ast_func_head *head, ast_block *block);

    ~ast_func_def() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_func_head *head;
    ast_block *block;

    llvm::BasicBlock *old_bb;

    void codegen_phase1();

    void codegen_phase2();

    void codegen_phase3();
};

#endif //MPC_AST_FUNC_DEF_H
