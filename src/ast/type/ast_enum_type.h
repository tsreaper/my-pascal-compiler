#ifndef MY_PASCAL_AST_ENUM_TYPE_H
#define MY_PASCAL_AST_ENUM_TYPE_H

#include <vector>

#include "ast/type/ast_type.h"

class ast_enum_type : public ast_type_node {
public:
    ast_enum_type();

    ~ast_enum_type() override;

    const sem_type &get_type() const override;

    void add_id(ast_id *id);

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    int enum_id = -1;
    sem_type s_type;
    std::vector<ast_id*> id_vec;
};

#endif //MY_PASCAL_AST_ENUM_TYPE_H
