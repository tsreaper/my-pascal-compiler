#ifndef MPC_AST_ARRAY_VAL_H
#define MPC_AST_ARRAY_VAL_H

#include "ast/val/literal/ast_literal.h"
#include "ast/exp/ast_exp_seq.h"

class ast_array_val : public ast_literal {
public:
    explicit ast_array_val(ast_exp_seq *value);

    ~ast_array_val() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_exp_seq *value;
};

#endif //MPC_AST_ARRAY_VAL_H
