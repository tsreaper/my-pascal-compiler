#ifndef MPC_SEM_SYS_FUNC_H
#define MPC_SEM_SYS_FUNC_H

#include "sem/type/sem_type.h"
#include "sem/func/sem_func.h"

namespace sem {
    const sem_type &get_sys_func_ret_type(const func_sign &sign);
}

#endif //MPC_SEM_SYS_FUNC_H
