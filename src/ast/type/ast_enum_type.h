#ifndef MPC_AST_ENUM_TYPE_H
#define MPC_AST_ENUM_TYPE_H

#include "ast/ast_node.h"
#include "ast/id/ast_id_seq.h"

class ast_enum_type : public ast_type_node {
public:
    explicit ast_enum_type(ast_id_seq *seq);

    ~ast_enum_type() override;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_id_seq *seq;
    int enum_id = -1;
};

#endif //MPC_AST_ENUM_TYPE_H
