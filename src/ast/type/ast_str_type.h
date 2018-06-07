#ifndef MPC_AST_STR_TYPE_H
#define MPC_AST_STR_TYPE_H

#include "ast/ast_node.h"

class ast_str_type : public ast_type_node {
public:
    explicit ast_str_type(ast_value_node *len_node = nullptr);

    ~ast_str_type() override = default;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_value_node *len_node;
    int len;
};

const int DEFAULT_STR_LEN = 255;

#endif //MPC_AST_STR_TYPE_H
