#ifndef MPC_GEN_ARITH_H
#define MPC_GEN_ARITH_H

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::Value *gen_arith_add(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_arith_sub(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_arith_mul(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_arith_div(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_arith_div_floor(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_arith_mod(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_arith_add_one(const sem_type &type, llvm::Value *value);

    llvm::Value *gen_arith_sub_one(const sem_type &type, llvm::Value *value);
}

#endif //MPC_GEN_ARITH_H
