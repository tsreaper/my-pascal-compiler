#include "sem/func/sys/sem_sys_copy.h"

const func_sign &sem::get_sys_copy_sign() {
    static func_sign copy_sign = {
            "copy",
            {non_built_in_type::STR_TYPE, built_in_type::INT_TYPE, built_in_type::INT_TYPE}
    };
    return copy_sign;
}
