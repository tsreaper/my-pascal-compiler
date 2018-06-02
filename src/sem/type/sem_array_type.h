#ifndef MPC_SEM_ARRAY_TYPE_H
#define MPC_SEM_ARRAY_TYPE_H

#include <vector>

#include "sem/type/sem_type.h"

struct sem_array_type {
    sem_type ele_type;
    int size;
    std::vector<int> range_vec;

    bool operator==(const sem_array_type &rhs) const;
};

namespace sem {
    int get_or_define_array_type(const sem_array_type &type);

    const sem_array_type &get_array_type_by_idx(int idx);

    void assert_is_array_value(const sem_type &type);
}

#endif //MPC_SEM_ARRAY_TYPE_H
