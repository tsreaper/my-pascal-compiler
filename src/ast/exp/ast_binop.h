#ifndef MPC_AST_BINOP_H
#define MPC_AST_BINOP_H

#include "ast/val/ast_rval.h"

class ast_binop : public ast_rval {
public:
    ast_binop(ast_value_node *child_l, ast_value_node *child_r);

    ~ast_binop() override;

protected:
    ast_value_node *child_l, *child_r;
    sem_type conv_type_l, conv_type_r;

    bool semantics_child() override;

    bool semantics_self() override;

    virtual bool semantics_op() = 0;

    void binop_explain_impl(const std::string &op_name, std::string &res, int indent) const;
};

#define GEN_PARAMS_NO_TYPE \
    gen::llvm_type_convert(child_l->get_type(), conv_type_l, child_l->get_llvm_value()), \
    gen::llvm_type_convert(child_r->get_type(), conv_type_r, child_r->get_llvm_value())

#define GEN_PARAMS \
    conv_type_l, \
    GEN_PARAMS_NO_TYPE

#endif //MPC_AST_BINOP_H
