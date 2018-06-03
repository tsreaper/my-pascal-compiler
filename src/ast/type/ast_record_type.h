#ifndef MPC_AST_RECORD_TYPE_H
#define MPC_AST_RECORD_TYPE_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id_seq_with_type.h"

class ast_record_type : public ast_type_node {
public:
    ~ast_record_type() override;

    void add_seq(ast_id_seq_with_type *seq);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    std::vector<ast_id_seq_with_type *> seq_vec;
    std::vector<ast_id *> id_vec;
    std::vector<sem_type> type_vec;
    int record_id = -1;
};

#endif //MPC_AST_RECORD_TYPE_H
