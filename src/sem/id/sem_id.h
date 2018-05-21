#ifndef MY_PASCAL_SEM_ID_H
#define MY_PASCAL_SEM_ID_H

#include <string>

#include "sem/type/sem_type.h"
#include "sem/value/sem_value.h"

sem_type get_id_type(const std::string &id);

sem_value get_id_value(const std::string &id);

#endif //MY_PASCAL_SEM_ID_H
