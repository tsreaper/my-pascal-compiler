#ifndef MY_PASCAL_AST_INTERFACE_H
#define MY_PASCAL_AST_INTERFACE_H

#include "sem/type/sem_type.h"
#include "sem/value/sem_value.h"

class ast_has_type {
public:
    virtual sem_type get_type() const = 0;
};

class ast_has_value {
public:
    virtual sem_value get_value() const = 0;
};

#endif //MY_PASCAL_AST_INTERFACE_H
