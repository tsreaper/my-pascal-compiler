#include "sem/func/sys/sem_sys_abs.h"

const func_sign &sem::get_sys_abs_int_sign() {
    static func_sign abs_int_sign = {"abs", {built_in_type::INT_TYPE}};
    return abs_int_sign;
}

const func_sign &sem::get_sys_abs_real_sign() {
    static func_sign abs_real_sign = {"abs", {built_in_type::REAL_TYPE}};
    return abs_real_sign;
}
