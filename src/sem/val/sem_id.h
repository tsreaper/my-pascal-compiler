#ifndef MPC_SEM_ID_H
#define MPC_SEM_ID_H

#include <string>

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

namespace sem {
    const sem_type &get_id_type(const std::string &id);

    const sem_value &get_id_value(const std::string &id);

    bool is_const_id(const std::string &id);

    bool is_declared_val(const std::string &id);

    void assert_is_variable(const std::string &id);
}

#endif //MPC_SEM_ID_H
