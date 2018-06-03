#ifndef MPC_GEN_SYS_FUNC_H
#define MPC_GEN_SYS_FUNC_H

#include "sem/func/sem_func.h"
#include "gen/func/sys/gen_all_sys_funcs.h"

namespace gen {
    llvm::Value *get_sys_func_call(const func_sign &sign, const std::vector<ast_value_node *> &args);
}

#endif //MPC_GEN_SYS_FUNC_H
