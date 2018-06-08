#ifndef MPC_SEM_SYS_INC_DEC_H
#define MPC_SEM_SYS_INC_DEC_H

#include <vector>

#include "sem/func/sem_func.h"

namespace sem {
    void assert_sys_inc_dec_args_type(const func_sign &sign, const std::vector<bool> &rval_vec);
}

#endif //MPC_SEM_SYS_INC_DEC_H
