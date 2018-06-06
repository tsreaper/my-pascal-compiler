#ifndef MPC_GEN_RECORD_TYPE_H
#define MPC_GEN_RECORD_TYPE_H

#include <llvm/IR/DerivedTypes.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::StructType *get_llvm_record_type(const sem_type &type);
}

#endif //MPC_GEN_RECORD_TYPE_H
