#ifndef MPC_SEM_SYS_MIN_MAX_H
#define MPC_SEM_SYS_MIN_MAX_H

#include "sem/func/sem_func.h"

namespace sem {
    const func_sign &get_sys_min_int_sign();

    const sem_type &get_sys_min_int_ret(const func_sign &);

    const func_sign &get_sys_max_int_sign();

    const sem_type &get_sys_max_int_ret(const func_sign &);

    const func_sign &get_sys_min_real_sign();

    const sem_type &get_sys_min_real_ret(const func_sign &);

    const func_sign &get_sys_max_real_sign();

    const sem_type &get_sys_max_real_ret(const func_sign &);
}

#endif //MPC_SEM_SYS_MIN_MAX_H
