#ifndef MPC_AST_REAL_VAL_H
#define MPC_AST_REAL_VAL_H

#include "ast/val/literal/ast_literal.h"

class ast_real_val : public ast_literal {
public:
    explicit ast_real_val(double value);

    void explain_impl(std::string &res, int indent) const override;

private:
    double value;

    void codegen() override;
};

#endif //MPC_AST_REAL_VAL_H
