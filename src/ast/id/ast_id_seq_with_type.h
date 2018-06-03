#ifndef MPC_AST_ID_SEQ_WITH_TYPE_H
#define MPC_AST_ID_SEQ_WITH_TYPE_H

#include "ast/ast_node.h"
#include "ast/id/ast_id_seq.h"

class ast_id_seq_with_type : public ast_node {
public:
    ast_id_seq_with_type(ast_id_seq *seq, ast_type_node *type);

    ~ast_id_seq_with_type() override;

    const std::vector<ast_id *> &get_id_vec() const;

    const sem_type &get_type() const;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    ast_id_seq *seq;
    ast_type_node *type;
};

#endif //MPC_AST_ID_SEQ_WITH_TYPE_H
