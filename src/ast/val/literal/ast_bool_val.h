#ifndef MPC_AST_BOOL_VAL_H
#define MPC_AST_BOOL_VAL_H

#include "ast/val/literal/ast_literal.h"

class ast_bool_val : public ast_literal {
public:
    explicit ast_bool_val(bool value);

    void explain_impl(std::string &res, int indent) const override;

private:
    bool value;

    void codegen() override;
};

#endif //MPC_AST_BOOL_VAL_H
