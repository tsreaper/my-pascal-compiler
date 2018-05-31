#ifndef MPC_AST_FUNC_DEC_H
#define MPC_AST_FUNC_DEC_H

#include "ast/func/ast_func_head.h"

class ast_func_dec : public ast_node {
public:
    explicit ast_func_dec(ast_func_head *head);

    ~ast_func_dec() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_func_head *head;
};

#endif //MPC_AST_FUNC_DEC_H
