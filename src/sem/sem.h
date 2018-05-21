#ifndef MY_PASCAL_SEM_H
#define MY_PASCAL_SEM_H

#include <vector>
#include <map>

#include "sem/func/sem_func.h"
#include "sem/label/sem_label.h"
#include "sem/type/sem_type.h"
#include "sem/type/sem_enum_type.h"
#include "sem/value/sem_const.h"

class sem_context {
public:
    void push();

    void pop();

    sem_label_context &get_label_env();

    sem_type_context &get_type_env();

    sem_const_context &get_const_env();

    sem_enum_context &get_enum_env();

    sem_func_context &get_func_env();

private:
    sem_label_context label_env;
    sem_type_context type_env;
    sem_const_context const_env;
    sem_enum_context enum_env;
    sem_func_context func_env;
};

extern sem_context sem_env;

#endif //MY_PASCAL_SEM_H
