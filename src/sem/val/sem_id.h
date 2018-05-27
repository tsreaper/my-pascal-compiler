#ifndef MY_PASCAL_SEM_ID_H
#define MY_PASCAL_SEM_ID_H

#include <string>

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

namespace sem {
    const sem_type &get_id_type(const std::string &id);

    const sem_value &get_id_value(const std::string &id);

    bool is_const_id(const std::string &id);

    bool is_used_id(const std::string &id);
}

#endif //MY_PASCAL_SEM_ID_H
