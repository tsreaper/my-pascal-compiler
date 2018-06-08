#ifndef MPC_SEM_SYS_FUNC_H
#define MPC_SEM_SYS_FUNC_H

#include <vector>

#include "sem/type/sem_type.h"
#include "sem/func/sem_func.h"

namespace sem {
    func_sign_ret get_sys_call_func_sign_ret(const func_sign &sign, const std::vector<bool> &rval_vec);
}

#endif //MPC_SEM_SYS_FUNC_H
