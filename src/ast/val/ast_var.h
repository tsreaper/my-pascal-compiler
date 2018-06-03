#ifndef MPC_AST_VAR_H
#define MPC_AST_VAR_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id_seq_with_type.h"

class ast_var_dec : public ast_node {
public:
    explicit ast_var_dec(ast_id_seq_with_type *seq);

    ~ast_var_dec() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

    void codegen() override;

private:
    ast_id_seq_with_type *seq;
};

class ast_var_dec_seq : public ast_node {
public:
    ~ast_var_dec_seq() override;

    void add_var_dec(ast_var_dec *dec);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    std::vector<ast_var_dec *> var_dec_vec;
};

#endif //MPC_AST_VAR_H
