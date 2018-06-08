#ifndef MPC_SEM_SYS_FILLCHAR_H
#define MPC_SEM_SYS_FILLCHAR_H

#include <vector>

#include "sem/func/sem_func.h"

namespace sem {
    void assert_sys_fillchar_args_type(const func_sign &sign, const std::vector<bool> &rval_vec);
}

#endif //MPC_SEM_SYS_FILLCHAR_H
