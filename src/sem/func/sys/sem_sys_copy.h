#ifndef MPC_SEM_SYS_COPY_H
#define MPC_SEM_SYS_COPY_H

#include "sem/func/sem_func.h"

namespace sem {
    const func_sign &get_sys_copy_sign();

    const sem_type &get_sys_copy_ret(const func_sign &sign);
}

#endif //MPC_SEM_SYS_COPY_H
