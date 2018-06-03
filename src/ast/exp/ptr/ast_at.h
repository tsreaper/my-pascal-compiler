#ifndef MPC_AST_AT_H
#define MPC_AST_AT_H

#include "ast/val/ast_rval.h"

class ast_at : public ast_rval {
public:
    explicit ast_at(ast_value_node *lval);

    ~ast_at() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *lval;
};

#endif //MPC_AST_AT_H
