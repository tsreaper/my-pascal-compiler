#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_sys_write.h"

void sem::assert_sys_write_args_type(const func_sign &sign) {
    for (auto &child : sign.param_type_vec) {
        if (
                child != built_in_type::INT_TYPE &&
                child != built_in_type::REAL_TYPE &&
                child != built_in_type::CHAR_TYPE &&
                child.tg != type_group::STR
        ) {
            throw sem_exception(
                    "semantics error, parameters of write must be integer, real, character or string value"
            );
        }
    }
}
