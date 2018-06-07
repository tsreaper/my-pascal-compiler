#ifndef MPC_SEM_SYS_ABS_H
#define MPC_SEM_SYS_ABS_H

#include "sem/func/sem_func.h"

namespace sem {
    const func_sign &get_sys_abs_int_sign();

    const sem_type &get_sys_abs_int_ret(const func_sign &);

    const func_sign &get_sys_abs_real_sign();

    const sem_type &get_sys_abs_real_ret(const func_sign &);
}

#endif //MPC_SEM_SYS_ABS_H
