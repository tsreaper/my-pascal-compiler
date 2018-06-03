#ifndef MPC_AST_CALL_H
#define MPC_AST_CALL_H

#include "ast/val/ast_rval.h"
#include "ast/id/ast_id.h"
#include "ast/exp/ast_exp_seq.h"
#include "sem/func/sem_func.h"

class ast_call : public ast_rval {
public:
    ast_call(ast_id *id, ast_exp_seq *param);

    ~ast_call() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    ast_id *id;
    ast_exp_seq *param;
    func_sign sign;

    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;
};

#endif //MPC_AST_CALL_H
