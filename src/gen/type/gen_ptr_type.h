#ifndef MPC_GEN_PTR_TYPE_H
#define MPC_GEN_PTR_TYPE_H

#include <llvm/IR/DerivedTypes.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::PointerType *get_llvm_ptr_type(const sem_type &type);

    llvm::PointerType *get_llvm_char_ptr_type();
}

#endif //MPC_GEN_PTR_TYPE_H
