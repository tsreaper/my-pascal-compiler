#ifndef MY_PASCAL_AST_CHAR_TYPE_H
#define MY_PASCAL_AST_CHAR_TYPE_H

#include "ast/type/builtin/ast_builtin_type.h"

class ast_char_type : public ast_builtin_type {
public:
    ast_char_type();

    void explain_impl(std::string &res, int indent) const override;
};

#endif //MY_PASCAL_AST_CHAR_TYPE_H
