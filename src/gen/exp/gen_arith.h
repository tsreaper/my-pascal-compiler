#ifndef MY_PASCAL_GEN_ARITH_H
#define MY_PASCAL_GEN_ARITH_H

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::Value *gen_arith_add(
            const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
    );

    llvm::Value *gen_arith_sub(
            const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
    );

    llvm::Value *gen_arith_mul(
            const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
    );

    llvm::Value *gen_arith_div(
            const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
    );

    llvm::Value *gen_arith_div_floor(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_arith_mod(llvm::Value *value_l, llvm::Value *value_r);
}

#endif //MY_PASCAL_GEN_ARITH_H
