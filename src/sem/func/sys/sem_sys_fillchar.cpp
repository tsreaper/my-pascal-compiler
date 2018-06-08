#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_sys_fillchar.h"

void sem::assert_sys_fillchar_args_type(const func_sign &sign, const std::vector<bool> &rval_vec) {
    if (sign.param_type_vec.size() != 3) {
        throw sem_exception("semantics error, number of parameters of fillchar must be 3");
    }
    if (rval_vec[0]) {
        throw sem_exception("semantics error, 1st parameter of fillchar must be a left value");
    }
    if (sign.param_type_vec[1] != built_in_type::INT_TYPE) {
        throw sem_exception("semantics error, 2nd parameter of fillchar must be an integer value");
    }
    if (
            sign.param_type_vec[2] != built_in_type::INT_TYPE &&
            sign.param_type_vec[2] != built_in_type::CHAR_TYPE &&
            sign.param_type_vec[2] != built_in_type::BOOL_TYPE
    ) {
        throw sem_exception(
                "semantics error, 3rd parameter of fillchar must be an integer, character or boolean value"
        );
    }
}
