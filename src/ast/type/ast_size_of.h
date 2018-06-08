#ifndef MPC_AST_SIZE_OF_H
#define MPC_AST_SIZE_OF_H

#include "ast/val/ast_rval.h"

class ast_size_of : public ast_rval {
public:
    explicit ast_size_of(ast_type_node *type);

    ~ast_size_of() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    void codegen() override;

private:
    ast_type_node *type;
};

#endif //MPC_AST_SIZE_OF_H
