#ifndef MPC_GEN_STR_TYPE_H
#define MPC_GEN_STR_TYPE_H

#include <llvm/IR/DerivedTypes.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::ArrayType *get_llvm_str_type(const sem_type &type);

    llvm::Value *gen_char_to_str_mem(llvm::Value *c);

    llvm::Value *gen_str_add(int dest_len, llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_str_eq(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_str_ne(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_str_lt(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_str_gt(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_str_le(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_str_ge(llvm::Value *value_l, llvm::Value *value_r);
}

#endif //MPC_GEN_STR_TYPE_H
