#include <vector>
#include <sem/val/sem_value.h>

#include "sem/exp/sem_cmp.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_range_type.h"

static std::vector<sem_range_type> range_type_vec;

bool sem_range_type::operator==(const sem_range_type &rhs) const {
    if (type != rhs.type) {
        return false;
    }
    return sem::do_cmp_eq(type, rhs.type, low, rhs.low).value.boo &&
           sem::do_cmp_eq(type, rhs.type, high, rhs.high).value.boo;
}

int sem::get_or_define_range_type(const sem_range_type &type) {
    for (int i = 0; i < range_type_vec.size(); i++) {
        if (type == range_type_vec[i]) {
            return i;
        }
    }

    auto ret = (int) range_type_vec.size();
    range_type_vec.emplace_back(type);
    return ret;
}

const sem_range_type &sem::get_range_type_by_idx(int idx) {
    return range_type_vec[idx];
}

void sem::assert_can_be_range(const sem_type &type_l, const sem_type &type_r) {
    if (type_l.is_type || type_r.is_type) {
        throw sem_exception("semantics error, must be two values");
    }
    if (type_l != type_r) {
        throw sem_exception("semantics error, two values must be of same type");
    }
    if (type_l == built_in_type::INT_TYPE) {
        return;
    }
    if (type_l == built_in_type::CHAR_TYPE) {
        return;
    }
    if (type_l.tg == type_group::ENUM) {
        return;
    }
    throw sem_exception("semantics error, must be integer, character or enum type");
}

int sem::get_range_length(const sem_range_type &type) {
    return get_bias_in_range(type, type.high) + 1;
}

int sem::get_bias_in_range(const sem_range_type &type, const sem_value &value) {
    if (type.type == built_in_type::CHAR_TYPE) {
        return value.value.chr - type.low.value.chr;
    } else {
        return value.value.num - type.low.value.num;
    }
}
