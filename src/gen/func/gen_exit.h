#ifndef MPC_GEN_EXIT_H
#define MPC_GEN_EXIT_H

#include <llvm/IR/Value.h>

namespace gen {
    void gen_exit(llvm::Value *ret_val = nullptr);
}

#endif //MPC_GEN_EXIT_H
