#include "sem/func/sys/sem_sys_math.h"

const func_sign &sem::get_sys_sqr_sign() {
    static func_sign sqr_sign = {"sqr", {built_in_type::REAL_TYPE}};
    return sqr_sign;
}

const sem_type &sem::get_sys_sqr_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_sqrt_sign() {
    static func_sign sqrt_sign = {"sqrt", {built_in_type::REAL_TYPE}};
    return sqrt_sign;
}

const sem_type &sem::get_sys_sqrt_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_exp_sign() {
    static func_sign exp_sign = {"exp", {built_in_type::REAL_TYPE}};
    return exp_sign;
}

const sem_type &sem::get_sys_exp_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_ln_sign() {
    static func_sign ln_sign = {"ln", {built_in_type::REAL_TYPE}};
    return ln_sign;
}

const sem_type &sem::get_sys_ln_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_sin_sign() {
    static func_sign sin_sign = {"sin", {built_in_type::REAL_TYPE}};
    return sin_sign;
}

const sem_type &sem::get_sys_sin_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_cos_sign() {
    static func_sign cos_sign = {"cos", {built_in_type::REAL_TYPE}};
    return cos_sign;
}

const sem_type &sem::get_sys_cos_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_tan_sign() {
    static func_sign tan_sign = {"tan", {built_in_type::REAL_TYPE}};
    return tan_sign;
}

const sem_type &sem::get_sys_tan_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_arcsin_sign() {
    static func_sign arcsin_sign = {"arcsin", {built_in_type::REAL_TYPE}};
    return arcsin_sign;
}

const sem_type &sem::get_sys_arcsin_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_arccos_sign() {
    static func_sign arccos_sign = {"arccos", {built_in_type::REAL_TYPE}};
    return arccos_sign;
}

const sem_type &sem::get_sys_arccos_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}

const func_sign &sem::get_sys_arctan_sign() {
    static func_sign arctan_sign = {"arctan", {built_in_type::REAL_TYPE}};
    return arctan_sign;
}

const sem_type &sem::get_sys_arctan_ret(const func_sign &) {
    return built_in_type::REAL_TYPE;
}
