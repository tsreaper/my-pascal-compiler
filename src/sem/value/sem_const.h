#ifndef MY_PASCAL_SEM_CONST_H
#define MY_PASCAL_SEM_CONST_H

#include <string>

#include "sem/type/sem_type.h"
#include "sem/value/sem_value.h"

void define_const_id(const std::string &id, sem_type type, sem_value value);

#endif //MY_PASCAL_SEM_CONST_H
