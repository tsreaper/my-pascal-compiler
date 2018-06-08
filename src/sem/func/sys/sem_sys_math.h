#ifndef MPC_SEM_SYS_MATH_H
#define MPC_SEM_SYS_MATH_H

#include "sem/func/sem_func.h"

namespace sem {
    const func_sign &get_sys_sqr_sign();

    const sem_type &get_sys_sqr_ret(const func_sign &);

    const func_sign &get_sys_sqrt_sign();

    const sem_type &get_sys_sqrt_ret(const func_sign &);

    const func_sign &get_sys_exp_sign();

    const sem_type &get_sys_exp_ret(const func_sign &);

    const func_sign &get_sys_ln_sign();

    const sem_type &get_sys_ln_ret(const func_sign &);

    const func_sign &get_sys_sin_sign();

    const sem_type &get_sys_sin_ret(const func_sign &);

    const func_sign &get_sys_cos_sign();

    const sem_type &get_sys_cos_ret(const func_sign &);

    const func_sign &get_sys_tan_sign();

    const sem_type &get_sys_tan_ret(const func_sign &);

    const func_sign &get_sys_arcsin_sign();

    const sem_type &get_sys_arcsin_ret(const func_sign &);

    const func_sign &get_sys_arccos_sign();

    const sem_type &get_sys_arccos_ret(const func_sign &);

    const func_sign &get_sys_arctan_sign();

    const sem_type &get_sys_arctan_ret(const func_sign &);
}

#endif //MPC_SEM_SYS_MATH_H
