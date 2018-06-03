#ifndef MPC_AST_LOGIC_OR_H
#define MPC_AST_LOGIC_OR_H

#include "ast/exp/logic/ast_logic.h"

class ast_logic_or : public ast_logic {
public:
    ast_logic_or(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_logic_or() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    void codegen_l() override;

    void codegen_r() override;

private:
    llvm::Value *llvm_tmp;
    llvm::BasicBlock *r_bb, *cont_bb;
};

#endif //MPC_AST_LOGIC_OR_H
