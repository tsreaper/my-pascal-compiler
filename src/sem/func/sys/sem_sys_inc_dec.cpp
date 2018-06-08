#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_sys_inc_dec.h"

void sem::assert_sys_inc_dec_args_type(const func_sign &sign, const std::vector<bool> &rval_vec) {
    if (sign.param_type_vec.empty() || sign.param_type_vec.size() > 2) {
        throw sem_exception("semantics error, number of parameters of inc/dec must be 1 or 2");
    }
    if (rval_vec[0]) {
        throw sem_exception("semantics error, 1st parameter of inc/dec must be a left value");
    }
    if (
            sign.param_type_vec[0] != built_in_type::INT_TYPE &&
            sign.param_type_vec[0] != built_in_type::CHAR_TYPE
    ) {
        throw sem_exception("semantics error, 1st parameter of inc/dec must be an integer or character value");
    }
    if (
            sign.param_type_vec.size() == 2 &&
            sign.param_type_vec[1] != built_in_type::INT_TYPE &&
            sign.param_type_vec[1] != built_in_type::CHAR_TYPE
    ) {
        throw sem_exception("semantics error, 2nd parameter of inc/dec must be an integer or character value");
    }
}
