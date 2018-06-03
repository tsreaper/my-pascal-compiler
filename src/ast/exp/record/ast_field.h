#ifndef MPC_AST_FIELD_H
#define MPC_AST_FIELD_H

#include "ast/ast_node.h"

class ast_field : public ast_value_node {
public:
    ast_field(ast_value_node *record, const std::string &name);

    ~ast_field() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_value_node *record;
    const std::string name;
};

#endif //MPC_AST_FIELD_H
