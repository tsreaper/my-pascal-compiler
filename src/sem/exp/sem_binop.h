#ifndef MPC_SEM_BINOP_H
#define MPC_SEM_BINOP_H

#include "sem/type/sem_type.h"

namespace sem {
    void binop_type_compare(const sem_type &type_l, const sem_type &type_r, sem_type &res_l, sem_type &res_r);
}

#endif //MPC_SEM_BINOP_H
