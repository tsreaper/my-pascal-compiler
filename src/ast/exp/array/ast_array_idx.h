#ifndef MPC_AST_ARRAY_IDX_H
#define MPC_AST_ARRAY_IDX_H

#include <vector>

#include "ast/val/ast_lhs.h"

class ast_array_idx : public ast_lhs {
public:
    explicit ast_array_idx(ast_lhs *arr);

    ~ast_array_idx() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    llvm::Value * get_llvm_mem() const override;

    void append_idx(ast_value_node *idx);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_lhs *arr;
    std::vector<ast_value_node *> idx_vec;
    sem_type s_type;
    sem_value s_value;

    llvm::Value *llvm_mem = nullptr;
};

#endif //MPC_AST_ARRAY_IDX_H
