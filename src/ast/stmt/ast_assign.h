#ifndef MY_PASCAL_AST_ASSIGN_H
#define MY_PASCAL_AST_ASSIGN_H

#include "ast/stmt/ast_stmt.h"
#include "ast/id/ast_id.h"

class ast_assign : public ast_stmt {
public:
    ast_assign(ast_id *id, ast_type_node *rhs);

    ~ast_assign() override;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    ast_type_node *rhs;
};

#endif //MY_PASCAL_AST_ASSIGN_H
