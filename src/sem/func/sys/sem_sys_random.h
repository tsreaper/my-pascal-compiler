#ifndef MPC_SEM_SYS_RANDOM_H
#define MPC_SEM_SYS_RANDOM_H

#include "sem/func/sem_func.h"

namespace sem {
    const func_sign &get_sys_random_sign();

    const sem_type &get_sys_random_ret(const func_sign &);

    const func_sign &get_sys_randomize_sign();

    const sem_type &get_sys_randomize_ret(const func_sign &);
}

#endif //MPC_SEM_SYS_RANDOM_H
