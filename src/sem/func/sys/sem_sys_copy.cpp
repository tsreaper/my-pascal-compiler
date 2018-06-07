#include "sem/type/sem_str_type.h"
#include "sem/func/sys/sem_sys_copy.h"

const func_sign &sem::get_sys_copy_sign() {
    static func_sign copy_sign = {
            "copy",
            {non_built_in_type::STR_TYPE, built_in_type::INT_TYPE, built_in_type::INT_TYPE}
    };
    return copy_sign;
}

const sem_type &sem::get_sys_copy_ret(const func_sign &sign) {
    return get_str_type_by_len(sign.param_type_vec[0].id);
}
