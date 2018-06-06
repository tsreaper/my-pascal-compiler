#ifndef MPC_GEN_TYPE_H
#define MPC_GEN_TYPE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::Type *get_llvm_type(const sem_type &type);
}

#endif //MPC_GEN_TYPE_H
