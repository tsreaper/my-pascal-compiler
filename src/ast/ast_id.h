#ifndef MY_PASCAL_AST_ID_H
#define MY_PASCAL_AST_ID_H

#include "ast_node.h"

class ast_id : public ast_value_node {
public:
    explicit ast_id(const char *id);

    type value_type() override;

    bool check() override;

    void explain_impl(std::string &res, int indent) override;

private:
    std::string id;
};

#endif //MY_PASCAL_AST_ID_H
