#ifndef MPC_AST_LABEL_H
#define MPC_AST_LABEL_H

#include <vector>

#include "ast/ast_node.h"

class ast_label_dec : public ast_node {
public:
    explicit ast_label_dec(int label);

    ~ast_label_dec() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_self() override;

private:
    int label;
};

class ast_label_dec_seq : public ast_node {
public:
    ~ast_label_dec_seq() override;

    void add_label_dec(ast_label_dec* dec);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    std::vector<ast_label_dec*> label_dec_vec;
};

#endif //MPC_AST_LABEL_H
