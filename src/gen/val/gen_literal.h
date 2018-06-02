#ifndef MPC_GEN_LITERAL_H
#define MPC_GEN_LITERAL_H

#include <llvm/IR/Constants.h>

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

namespace gen {
    llvm::Constant *get_llvm_const(const sem_type &type, const sem_value &value);

    llvm::Constant *get_llvm_init_val(const sem_type &type);

    llvm::Constant *get_llvm_builtin_init_val(const sem_type &type);

    llvm::Constant *get_llvm_int(const sem_value &value);

    llvm::Constant *get_llvm_real(const sem_value &value);

    llvm::Constant *get_llvm_char(const sem_value &value);

    llvm::Constant *get_llvm_bool(const sem_value &value);
}

#endif //MPC_GEN_LITERAL_H
