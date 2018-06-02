#include "sem/exp/sem_arith.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_range_type.h"
#include "sem/type/sem_array_type.h"

std::vector<sem_array_type> array_type_vec;

bool sem_array_type::operator==(const sem_array_type &rhs) const {
    if (ele_type != rhs.ele_type) {
        return false;
    }
    if (size != rhs.size) {
        return false;
    }
    for (int i = 0; i < range_vec.size(); i++) {
        if (range_vec[i] != rhs.range_vec[i]) {
            return false;
        }
    }
    return true;
}

int sem::get_or_define_array_type(const sem_array_type &type) {
    for (int i = 0; i < array_type_vec.size(); i++) {
        if (type == array_type_vec[i]) {
            return i;
        }
    }

    auto ret = (int) array_type_vec.size();
    array_type_vec.emplace_back(type);
    return ret;
}

const sem_array_type &sem::get_array_type_by_idx(int idx) {
    return array_type_vec[idx];
}

void sem::assert_is_array_value(const sem_type &type) {
    if (type.is_type || type.tg != type_group::ARRAY) {
        throw sem_exception("semantics error, must be an array value");
    }
}
