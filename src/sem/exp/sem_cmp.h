#ifndef MPC_SEM_CMP_H
#define MPC_SEM_CMP_H

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

namespace sem {
    sem_value do_cmp_eq(
            const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
    );

    sem_value do_cmp_ne(
            const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
    );

    sem_value do_cmp_lt(
            const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
    );

    sem_value do_cmp_gt(
            const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
    );

    sem_value do_cmp_le(
            const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
    );

    sem_value do_cmp_ge(
            const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
    );
}

#endif //MPC_SEM_CMP_H
