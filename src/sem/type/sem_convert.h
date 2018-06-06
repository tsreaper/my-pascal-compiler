#ifndef MPC_SEM_CONVERT_H
#define MPC_SEM_CONVERT_H

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

namespace sem {
    sem_value sem_type_convert(const sem_type &src_type, const sem_type &dest_type, const sem_value &value);
}

#endif //MPC_SEM_CONVERT_H
