#ifndef MPC_AST_AT_H
#define MPC_AST_AT_H

#include "ast/ast_node.h"
#include "ast/val/ast_id.h"

class ast_at : public ast_value_node {
public:
    explicit ast_at(ast_id *id);

    ~ast_at() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_id *id;
    sem_type s_type;
    sem_value s_value;
};

#endif //MPC_AST_AT_H
