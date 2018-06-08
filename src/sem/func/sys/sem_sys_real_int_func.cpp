#include "sem/func/sys/sem_sys_real_int_func.h"

const func_sign &sem::get_sys_int_sign() {
    static func_sign int_sign = {"int", {built_in_type::REAL_TYPE}};
    return int_sign;
}

const sem_type &sem::get_sys_int_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_frac_sign() {
    static func_sign frac_sign = {"frac", {built_in_type::REAL_TYPE}};
    return frac_sign;
}

const sem_type &sem::get_sys_frac_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_trunc_sign() {
    static func_sign trunc_sign = {"trunc", {built_in_type::REAL_TYPE}};
    return trunc_sign;
}

const sem_type &sem::get_sys_trunc_ret(const func_sign &) {
    return built_in_type::INT_TYPE;
}

const func_sign &sem::get_sys_round_sign() {
    static func_sign round_sign = {"round", {built_in_type::REAL_TYPE}};
    return round_sign;
}

const sem_type &sem::get_sys_round_ret(const func_sign &) {
    return built_in_type::INT_TYPE;
}
