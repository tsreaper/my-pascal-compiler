#ifndef MPC_GEN_CMP_H
#define MPC_GEN_CMP_H

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::Value *gen_cmp_eq(const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_cmp_ne(const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_cmp_lt(const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_cmp_gt(const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_cmp_le(const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_cmp_ge(const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r);
}

#endif //MPC_GEN_CMP_H
