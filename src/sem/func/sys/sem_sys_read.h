#ifndef MPC_SEM_SYS_READ_H
#define MPC_SEM_SYS_READ_H

#include <vector>

#include "sem/func/sem_func.h"

namespace sem {
    void assert_sys_read_args_type(const func_sign &sign, const std::vector<bool> &rval_vec);
}

#endif //MPC_SEM_SYS_READ_H
