#include "sem/exception/sem_exception.h"
#include "sem/sem.h"

sem_context sem_env;

void sem_context::push(const func_sign &current_sign) {
    depth++;
    label_env.push();
    type_env.push();
    const_env.push();
    enum_env.push();
    record_env.push();
    func_env.push(current_sign);
}

void sem_context::pop() {
    depth--;
    label_env.pop();
    type_env.pop();
    const_env.pop();
    enum_env.pop();
    record_env.pop();
    func_env.pop();
}

bool sem_context::is_global() const {
    return depth == 1;
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

sem_record_context &sem_context::get_record_env() {
    return record_env;
}

sem_func_context &sem_context::get_func_env() {
    return func_env;
}

sem_loop_context &sem_context::get_loop_env() {
    return loop_env;
}
