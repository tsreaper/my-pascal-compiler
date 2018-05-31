#ifndef MPC_AST_ENUM_TYPE_H
#define MPC_AST_ENUM_TYPE_H

#include <vector>

#include "ast/type/ast_type.h"

class ast_enum_type : public ast_type_node {
public:
    ast_enum_type();

    ~ast_enum_type() override;

    const sem_type &get_type() const override;

    void add_id(ast_id *id);

    void explain_impl(std::string &res, int indent) const override;

protected:
    bool semantics_child() override;

    bool semantics_self() override;

private:
    std::vector<ast_id*> id_vec;
    int enum_id = -1;
    sem_type s_type;
};

#endif //MPC_AST_ENUM_TYPE_H
