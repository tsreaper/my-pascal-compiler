#ifndef MPC_AST_BOOL_TYPE_H
#define MPC_AST_BOOL_TYPE_H

#include "ast/type/builtin/ast_builtin_type.h"

class ast_bool_type : public ast_builtin_type {
public:
    ast_bool_type();

    void explain_impl(std::string &res, int indent) const override;
};

#endif //MPC_AST_BOOL_TYPE_H
