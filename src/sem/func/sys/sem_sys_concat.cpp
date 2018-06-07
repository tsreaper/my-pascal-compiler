#include "sem/type/sem_str_type.h"
#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_sys_concat.h"

void sem::assert_sys_concat_args_type(const func_sign &sign) {
    if (sign.param_type_vec.size() < 2) {
        throw sem_exception("semantics error, concat function should have at least 2 parameters");
    }
    for (auto &child : sign.param_type_vec) {
        if (
                child.tg != type_group::STR &&
                child != built_in_type::CHAR_TYPE
        ) {
            throw sem_exception("semantics error, parameters of concat function must be string or char values");
        }
    }
}

const sem_type &sem::get_sys_concat_ret(const func_sign &sign) {
    int len = 0;
    for (auto &child : sign.param_type_vec) {
        len += child.id;
    }
    return get_str_type_by_len(len);
}
