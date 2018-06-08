#include "sem/func/sys/sem_sys_random.h"

const func_sign &sem::get_sys_random_sign() {
    static func_sign random_sign = {"random", {built_in_type::INT_TYPE}};
    return random_sign;
}

const sem_type &sem::get_sys_random_ret(const func_sign &) {
    return built_in_type::INT_TYPE;
}

const func_sign &sem::get_sys_randomize_sign() {
    static func_sign randomize_sign = {"randomize", {}};
    return randomize_sign;
}

const sem_type &sem::get_sys_randomize_ret(const func_sign &) {
    return built_in_type::VOID_TYPE;
}
