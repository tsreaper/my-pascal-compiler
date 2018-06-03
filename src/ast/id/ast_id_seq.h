#ifndef MPC_AST_ID_SEQ_H
#define MPC_AST_ID_SEQ_H

#include <vector>

#include "ast/ast_node.h"
#include "ast/id/ast_id.h"

class ast_id_seq : public ast_node {
public:
    ~ast_id_seq() override;

    void add_id(ast_id *id);

    const std::vector<ast_id *> &get_id_vec() const;

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

private:
    std::vector<ast_id *> id_vec;
};

#endif //MPC_AST_ID_SEQ_H
