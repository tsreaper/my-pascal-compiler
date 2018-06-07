#ifndef MPC_SEM_STR_TYPE_H
#define MPC_SEM_STR_TYPE_H

#include "sem/type/sem_type.h"
#include "sem/type/sem_array_type.h"

namespace sem {
    void assert_is_str_value(const sem_type &type);

    sem_array_type get_str_array_type(const sem_type &type);
}

#endif //MPC_SEM_STR_TYPE_H
