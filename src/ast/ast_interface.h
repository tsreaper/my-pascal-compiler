#ifndef MY_PASCAL_AST_INTERFACE_H
#define MY_PASCAL_AST_INTERFACE_H

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

class ast_has_type {
public:
    virtual const sem_type &get_type() const = 0;
};

class ast_has_value {
public:
    virtual const sem_value &get_value() const = 0;

    llvm::Value *get_llvm_value() const;

protected:
    llvm::Value *llvm_value;
};

#endif //MY_PASCAL_AST_INTERFACE_H
