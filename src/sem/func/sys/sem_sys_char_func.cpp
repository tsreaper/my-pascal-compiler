#include "sem/func/sys/sem_sys_char_func.h"

const func_sign &sem::get_sys_chr_sign() {
    static func_sign chr_sign = {"chr", {built_in_type::INT_TYPE}};
    return chr_sign;
}

const sem_type &sem::get_sys_chr_ret(const func_sign &) {
    return built_in_type::CHAR_TYPE;
}

const func_sign &sem::get_sys_ord_sign() {
    static func_sign ord_sign = {"ord", {built_in_type::CHAR_TYPE}};
    return ord_sign;
}

const sem_type &sem::get_sys_ord_ret(const func_sign &) {
    return built_in_type::INT_TYPE;
}

const func_sign &sem::get_sys_succ_sign() {
    static func_sign succ_sign = {"succ", {built_in_type::CHAR_TYPE}};
    return succ_sign;
}

const sem_type &sem::get_sys_succ_ret(const func_sign &) {
    return built_in_type::CHAR_TYPE;
}

const func_sign &sem::get_sys_pred_sign() {
    static func_sign pred_sign = {"pred", {built_in_type::CHAR_TYPE}};
    return pred_sign;
}

const sem_type &sem::get_sys_pred_ret(const func_sign &) {
    return built_in_type::CHAR_TYPE;
}
