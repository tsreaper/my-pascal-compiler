#ifndef MPC_SEM_SYS_REAL_INT_FUNC_H
#define MPC_SEM_SYS_REAL_INT_FUNC_H

#include "sem/func/sem_func.h"

namespace sem {
    const func_sign &get_sys_int_sign();

    const sem_type &get_sys_int_ret(const func_sign &);

    const func_sign &get_sys_frac_sign();

    const sem_type &get_sys_frac_ret(const func_sign &);

    const func_sign &get_sys_trunc_sign();

    const sem_type &get_sys_trunc_ret(const func_sign &);

    const func_sign &get_sys_round_sign();

    const sem_type &get_sys_round_ret(const func_sign &);
}

#endif //MPC_SEM_SYS_REAL_INT_FUNC_H
