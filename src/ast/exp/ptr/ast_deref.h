#ifndef MPC_AST_DEREF_H
#define MPC_AST_DEREF_H

#include "ast/ast_node.h"

class ast_deref : public ast_value_node {
public:
    explicit ast_deref(ast_value_node *ptr);

    ~ast_deref() override;

    llvm::Value *get_llvm_mem() const override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *ptr;
};

#endif //MPC_AST_DEREF_H
