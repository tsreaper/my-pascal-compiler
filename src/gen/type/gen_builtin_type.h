#ifndef MPC_GEN_BUILTIN_TYPE_H
#define MPC_GEN_BUILTIN_TYPE_H

#include <llvm/IR/Type.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::Type *get_builtin_type(const sem_type &type);

    llvm::Type *get_llvm_int_type();

    llvm::Type *get_llvm_real_type();

    llvm::Type *get_llvm_char_type();

    llvm::Type *get_llvm_bool_type();

    llvm::Type *get_llvm_void_type();
}

#endif //MPC_GEN_BUILTIN_TYPE_H
