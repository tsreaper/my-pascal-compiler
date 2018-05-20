#ifndef MY_PASCAL_AST_INTERFACE_H
#define MY_PASCAL_AST_INTERFACE_H

#include "env/env_type.h"
#include "env/env_value.h"

class ast_has_type {
public:
    virtual env_type get_type() const = 0;
};

class ast_has_value {
public:
    virtual env_value get_value() const = 0;
};

#endif //MY_PASCAL_AST_INTERFACE_H
