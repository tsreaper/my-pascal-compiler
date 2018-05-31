#ifndef MPC_SEM_LOGIC_H
#define MPC_SEM_LOGIC_H

#include "sem/val/sem_value.h"

namespace sem {
    sem_value do_logic_and(const sem_value &value_l, const sem_value &value_r);

    sem_value do_logic_or(const sem_value &value_l, const sem_value &value_r);

    sem_value do_logic_xor(const sem_value &value_l, const sem_value &value_r);

    sem_value do_logic_not(const sem_value &value);
}

#endif //MPC_SEM_LOGIC_H
