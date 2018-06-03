#ifndef MPC_AST_ARRAY_TYPE_H
#define MPC_AST_ARRAY_TYPE_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/type/ast_range_type.h"

class ast_array_type : public ast_type_node {
public:
    ~ast_array_type() override;

    void append_range(ast_range_type *range);

    void set_ele_type(ast_type_node *ele_type);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    std::vector<ast_range_type *> range_vec;
    ast_type_node *ele_type;
    int type_id = -1;
};

#endif //MPC_AST_ARRAY_TYPE_H
