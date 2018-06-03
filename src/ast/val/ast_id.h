#ifndef MPC_AST_ID_H
#define MPC_AST_ID_H

#include "ast/ast_node.h"

class ast_id : public ast_value_node {
public:
    explicit ast_id(const char *id);

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    const std::string &get_id() const;

    llvm::Value *get_llvm_mem() const override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

    void codegen() override;

private:
    std::string id;
};

#endif //MPC_AST_ID_H
