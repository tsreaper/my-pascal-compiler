#ifndef MPC_SEM_H
#define MPC_SEM_H

#include <vector>
#include <map>

#include "sem/func/sem_func.h"
#include "sem/label/sem_label.h"
#include "sem/stmt/sem_loop.h"
#include "sem/type/sem_type.h"
#include "sem/type/sem_enum_type.h"
#include "sem/type/sem_record_type.h"
#include "sem/val/sem_const.h"

class sem_context {
public:
    void push();

    void pop();

    sem_label_context &get_label_env();

    sem_type_context &get_type_env();

    sem_const_context &get_const_env();

    sem_enum_context &get_enum_env();

    sem_record_context &get_record_env();

    sem_func_context &get_func_env();

    sem_loop_context &get_loop_env();

private:
    sem_label_context label_env;
    sem_type_context type_env;
    sem_const_context const_env;
    sem_enum_context enum_env;
    sem_record_context record_env;
    sem_func_context func_env;
    sem_loop_context loop_env;
};

extern sem_context sem_env;

#endif //MPC_SEM_H
