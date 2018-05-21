#ifndef MY_PASCAL_AST_ID_H
#define MY_PASCAL_AST_ID_H

#include "ast/ast_node.h"

class ast_id : public ast_value_node {
public:
    explicit ast_id(const char *id);

    sem_type get_type() const override;

    sem_value get_value() const override;

    const std::string &get_id() const;

    bool analyse() override;

    void explain_impl(std::string &res, int indent) const override;

private:
    std::string id;
};

#endif //MY_PASCAL_AST_ID_H
