#include "sem/exception/sem_exception.h"
#include "sem/sem.h"

sem_context sem_env;

void sem_context::push() {
    label_env.push();
    type_env.push();
    const_env.push();
    enum_env.push();
    func_env.push();
}

void sem_context::pop() {
    label_env.pop();
    type_env.pop();
    const_env.pop();
    enum_env.pop();
    func_env.pop();
}

sem_label_context &sem_context::get_label_env() {
    return label_env;
}

sem_type_context &sem_context::get_type_env() {
    return type_env;
}

sem_const_context &sem_context::get_const_env() {
    return const_env;
}

sem_enum_context &sem_context::get_enum_env() {
    return enum_env;
}

sem_func_context &sem_context::get_func_env() {
    return func_env;
}

sem_loop_context &sem_context::get_loop_env() {
    return loop_env;
}
