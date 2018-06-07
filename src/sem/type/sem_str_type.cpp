#include "sem/type/sem_range_type.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_str_type.h"

void sem::assert_is_str_value(const sem_type &type) {
    if (type.is_type || type.tg != type_group::STR || type.ptr > 0) {
        throw sem_exception("semantics error, must be a string value");
    }
}

sem_array_type sem::get_str_array_type(const sem_type &type) {
    return sem_array_type{
        built_in_type::CHAR_TYPE, 1,
        {get_or_define_range_type(make_int_range_type(1, type.id))}
    };
}
