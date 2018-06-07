#ifndef MPC_SEM_SYS_CONCAT_H
#define MPC_SEM_SYS_CONCAT_H

#include "sem/func/sem_func.h"

namespace sem {
    void assert_sys_concat_args_type(const func_sign &sign);

    const sem_type &get_sys_concat_ret(const func_sign &sign);
}

#endif //MPC_SEM_SYS_CONCAT_H
