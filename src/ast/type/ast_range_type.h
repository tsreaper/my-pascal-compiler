#ifndef MPC_AST_RANGE_TYPE_H
#define MPC_AST_RANGE_TYPE_H

#include "ast/ast_node.h"
#include "sem/type/sem_range_type.h"

class ast_range_type : public ast_type_node {
public:
    ast_range_type(ast_value_node *low, ast_value_node *high);

    ~ast_range_type() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_value_node *low, *high;
    int range_id = -1;
};

#endif //MPC_AST_RANGE_TYPE_H
