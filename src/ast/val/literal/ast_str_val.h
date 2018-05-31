#ifndef MPC_AST_STR_VAL_H
#define MPC_AST_STR_VAL_H

#include <string>

#include "ast/val/literal/ast_literal.h"

class ast_str_val : public ast_literal {
public:
    explicit ast_str_val(const char *value);

    void explain_impl(std::string &res, int indent) const override;

private:
    std::string value;

    // TODO codegen
};

#endif //MPC_AST_STR_VAL_H
