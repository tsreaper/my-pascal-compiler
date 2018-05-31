#ifndef MPC_AST_CASE_H
#define MPC_AST_CASE_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/exp/ast_exp_seq.h"

class ast_case : public ast_node {
public:
    explicit ast_case(ast_value_node *lhs);

    ~ast_case() override;

    void add_seq(ast_exp_seq *seq, ast_node *body);

    void set_default(ast_node *body);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_value_node *lhs;
    std::vector<ast_exp_seq *> seq_vec;
    std::vector<ast_node *> body_vec;
    ast_node *default_body = nullptr;

    std::vector<llvm::BasicBlock *> seq_block_vec;
    std::vector<llvm::BasicBlock *> body_block_vec;
    llvm::BasicBlock *default_block, *cont_block;

    bool semantics_lhs();

    bool semantics_seq(ast_exp_seq *seq);

    bool semantics_body(ast_node *body);

    bool semantics_default();

    void codegen_before();

    void codegen_seq(ast_exp_seq *seq, llvm::BasicBlock *body_block, llvm::BasicBlock *nxt_block);

    void codegen_body(llvm::BasicBlock *nxt_block);

    void codegen_default();
};

#endif //MPC_AST_CASE_H
