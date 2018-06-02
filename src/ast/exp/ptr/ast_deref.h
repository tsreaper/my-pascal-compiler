#ifndef MPC_AST_DEREF_H
#define MPC_AST_DEREF_H

#include "ast/val/ast_lhs.h"

class ast_deref : public ast_lhs {
public:
    explicit ast_deref(ast_value_node *ptr);

    ~ast_deref() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    llvm::Value *get_llvm_mem() const override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *ptr;
    sem_type s_type;
    sem_value s_value;
};

#endif //MPC_AST_DEREF_H
