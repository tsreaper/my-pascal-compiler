#ifndef MPC_SEM_SYS_CHAR_FUNC_H
#define MPC_SEM_SYS_CHAR_FUNC_H

#include "sem/func/sem_func.h"

namespace sem {
    const func_sign &get_sys_chr_sign();

    const sem_type &get_sys_chr_ret(const func_sign &);

    const func_sign &get_sys_ord_sign();

    const sem_type &get_sys_ord_ret(const func_sign &);

    const func_sign &get_sys_succ_sign();

    const sem_type &get_sys_succ_ret(const func_sign &);

    const func_sign &get_sys_pred_sign();

    const sem_type &get_sys_pred_ret(const func_sign &);
}

#endif //MPC_SEM_SYS_CHAR_FUNC_H
