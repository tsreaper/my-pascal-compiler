#include "sem/func/sys/sem_sys_min_max.h"

const func_sign &sem::get_sys_min_int_sign() {
    static func_sign min_int_sign = {"min", {built_in_type::INT_TYPE, built_in_type::INT_TYPE}};
    return min_int_sign;
}

const sem_type &sem::get_sys_min_int_ret(const func_sign &) {
    return built_in_type::INT_TYPE;
}

const func_sign &sem::get_sys_max_int_sign() {
    static func_sign max_int_sign = {"max", {built_in_type::INT_TYPE, built_in_type::INT_TYPE}};
    return max_int_sign;
}

const sem_type &sem::get_sys_max_int_ret(const func_sign &) {
    return built_in_type::INT_TYPE;
}

const func_sign &sem::get_sys_min_real_sign() {
    static func_sign min_real_sign = {"min", {built_in_type::REAL_TYPE, built_in_type::REAL_TYPE}};
    return min_real_sign;
}

const sem_type &sem::get_sys_min_real_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_max_real_sign() {
    static func_sign max_real_sign = {"max", {built_in_type::REAL_TYPE, built_in_type::REAL_TYPE}};
    return max_real_sign;
}

const sem_type &sem::get_sys_max_real_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}
