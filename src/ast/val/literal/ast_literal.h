#ifndef MY_PASCAL_AST_LITERAL_H
#define MY_PASCAL_AST_LITERAL_H

#include "ast/ast_node.h"
#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

class ast_literal : public ast_value_node {
public:
    const sem_type &get_type() const override;

    const sem_value &get_value() const override;

protected:
    sem_type s_type{};
    sem_value s_value{};
};

#endif //MY_PASCAL_AST_LITERAL_H
