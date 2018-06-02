#ifndef MPC_AST_PTR_TYPE_H
#define MPC_AST_PTR_TYPE_H

#include "ast/ast_node.h"

class ast_ptr_type : public ast_type_node {
public:
    explicit ast_ptr_type(ast_type_node *domain);

    ~ast_ptr_type() override;

    const sem_type &get_type() const override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_type_node *domain;
    sem_type s_type;
};

#endif //MPC_AST_PTR_TYPE_H
