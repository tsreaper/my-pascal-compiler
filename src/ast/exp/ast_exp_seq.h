#ifndef MPC_AST_EXP_SEQ_H
#define MPC_AST_EXP_SEQ_H

#include <vector>

#include "ast/ast_node.h"

class ast_exp_seq : public ast_node {
public:
    ~ast_exp_seq() override;

    void add_exp(ast_value_node *exp);

    const std::vector<ast_value_node *> &get_exp_vec() const;

    int get_size() const;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    std::vector<ast_value_node *> exp_vec;
};

#endif //MPC_AST_EXP_SEQ_H
