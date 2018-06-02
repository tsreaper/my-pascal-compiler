#ifndef MPC_GEN_TYPE_H
#define MPC_GEN_TYPE_H

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"

namespace gen {
    llvm::Type *get_llvm_type(const sem_type &type);

    llvm::Type *get_builtin_type(const sem_type &type);

    llvm::Type *get_llvm_int_type();

    llvm::Type *get_llvm_real_type();

    llvm::Type *get_llvm_char_type();

    llvm::Type *get_llvm_bool_type();

    llvm::Type *get_llvm_void_type();

    void to_llvm_arith_type(const sem_type &type_l, const sem_type &type_r, llvm::Value **value_l, llvm::Value **value_r);

    void to_llvm_real_type(const sem_type &type, llvm::Value **value);
}

#endif //MPC_GEN_TYPE_H
