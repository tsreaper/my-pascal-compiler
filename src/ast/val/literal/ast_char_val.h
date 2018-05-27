#ifndef MY_PASCAL_AST_CHAR_VAL_H
#define MY_PASCAL_AST_CHAR_VAL_H

#include "ast/val/literal/ast_literal.h"

class ast_char_val : public ast_literal {
public:
    explicit ast_char_val(char value);

    void explain_impl(std::string &res, int indent) const override;

private:
    char value;

    void codegen() override;
};

#endif //MY_PASCAL_AST_CHAR_VAL_H
