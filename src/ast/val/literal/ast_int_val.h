#ifndef MY_PASCAL_AST_INT_VAL_H
#define MY_PASCAL_AST_INT_VAL_H

#include "ast/val/literal/ast_literal.h"

class ast_int_val : public ast_literal {
public:
    explicit ast_int_val(int value);

    void explain_impl(std::string &res, int indent) const override;

private:
    int value;

    void codegen() override;
};

#endif //MY_PASCAL_AST_INT_VAL_H
