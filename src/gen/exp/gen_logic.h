#ifndef MPC_GEN_LOGIC_H
#define MPC_GEN_LOGIC_H

#include <llvm/IR/Value.h>

namespace gen {
    llvm::Value *gen_logic_and(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_logic_or(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_logic_xor(llvm::Value *value_l, llvm::Value *value_r);

    llvm::Value *gen_logic_not(llvm::Value *value);
}

#endif //MPC_GEN_LOGIC_H
