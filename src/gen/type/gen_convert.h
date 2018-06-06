#ifndef MPC_GEN_CONVERT_H
#define MPC_GEN_CONVERT_H

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::Value *llvm_type_convert(const sem_type &src_t, const sem_type &dest_t, llvm::Value *value);
}

#endif //MPC_GEN_CONVERT_H
