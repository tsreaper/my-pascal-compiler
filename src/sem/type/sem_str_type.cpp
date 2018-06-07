#include <map>

#include "sem/type/sem_range_type.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_str_type.h"

void sem::assert_is_str_value(const sem_type &type) {
    if (type.is_type || type.tg != type_group::STR || type.ptr > 0) {
        throw sem_exception("semantics error, must be a string value");
    }
}

const sem_type &sem::get_str_type_by_len(int len) {
    static std::map<int, sem_type> str_type_pool;
    if (str_type_pool.find(len) == str_type_pool.end()) {
        str_type_pool[len] = {true, type_group::STR, len};
    }
    return str_type_pool.at(len);
}

const sem_type &sem::get_str_val_by_len(int len) {
    static std::map<int, sem_type> str_val_pool;
    if (str_val_pool.find(len) == str_val_pool.end()) {
        str_val_pool[len] = {false, type_group::STR, len};
    }
    return str_val_pool.at(len);
}

sem_array_type sem::get_str_array_type(const sem_type &type) {
    return sem_array_type{
        built_in_type::CHAR_TYPE, 1,
        {get_or_define_range_type(make_int_range_type(1, type.id))}
    };
}
