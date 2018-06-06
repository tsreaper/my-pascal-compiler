#include <sem/val/sem_value.h>
#include "sem/type/sem_convert.h"

sem_value sem::sem_type_convert(const sem_type &src_type, const sem_type &dest_type, const sem_value &value) {
    if (src_type == built_in_type::INT_TYPE && dest_type == built_in_type::REAL_TYPE) {
        sem_value ret = value;
        ret.value.real = ret.value.num;
        return ret;
    }
    return value;
}
