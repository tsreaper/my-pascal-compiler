#ifndef MPC_AST_CALL_H
#define MPC_AST_CALL_H

#include "ast/ast_node.h"
#include "ast/val/ast_id.h"
#include "ast/exp/ast_exp_seq.h"
#include "sem/func/sem_func.h"

class ast_call : public ast_value_node {
public:
    ast_call(ast_id *id, ast_exp_seq *param);

    ~ast_call() override;

    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    ast_exp_seq *param;
    sem_type s_type;
    sem_value s_value;
    func_sign sign;

    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;
};

#endif //MPC_AST_CALL_H
