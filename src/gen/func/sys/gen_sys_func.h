#ifndef MPC_GEN_SYS_FUNC_H
#define MPC_GEN_SYS_FUNC_H

#include "sem/func/sem_func.h"
#include "gen/func/sys/gen_all_sys_funcs.h"

namespace gen {
    llvm::Value *get_sys_func_call(const func_sign &sign, const std::vector<ast_value_node *> &args);
}

#define RETURN_C_FUNC(name) { \
    llvm::Function *func = llvm::Function::Create( \
        func_type, llvm::Function::ExternalLinkage, name, &llvm_module \
    ); \
    func->setCallingConv(llvm::CallingConv::C); \
    return func; \
}

#endif //MPC_GEN_SYS_FUNC_H
