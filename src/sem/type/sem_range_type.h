#ifndef MPC_SEM_RANGE_TYPE_H
#define MPC_SEM_RANGE_TYPE_H

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

struct sem_range_type {
    sem_type type;
    sem_value low, high;

    bool operator==(const sem_range_type &rhs) const;
};

namespace sem {
    sem_range_type make_int_range_type(int low, int high);

    int get_or_define_range_type(const sem_range_type &type);

    const sem_range_type &get_range_type_by_idx(int idx);

    void assert_can_be_range(const sem_type &type_l, const sem_type &type_r);

    int get_range_length(const sem_range_type &type);

    int get_bias_in_range(const sem_range_type &type, const sem_value &value);
}

#endif //MPC_SEM_RANGE_TYPE_H
