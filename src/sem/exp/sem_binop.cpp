#include <vector>

#include "sem/exception/sem_exception.h"
#include "sem/exp/sem_binop.h"

void sem::binop_type_compare(
        const sem_type &type_l, const sem_type &type_r, sem_type &res_l, sem_type &res_r
) {
    if (type_l.is_type || type_r.is_type) {
        throw sem_exception("semantics error, only values can be operands");
    }

    // Same type?
    if (type_l == type_r) {
        res_l = res_r = type_l;
        return;
    }

    // Two string type?
    if (type_l.tg == type_group::STR && type_r.tg == type_group::STR) {
        res_l = type_l;
        res_r = type_r;
        return;
    }

    static std::vector<std::pair<std::pair<sem_type, sem_type>, sem_type>> table = {
            {{built_in_type::REAL_VAL, built_in_type::INT_VAL}, built_in_type::REAL_VAL},
            {{built_in_type::INT_VAL, built_in_type::REAL_VAL}, built_in_type::REAL_VAL}
    };
    for (auto &e : table) {
        if (e.first.first == type_l && e.first.second == type_r) {
            res_l = res_r = e.second;
            return;
        }
    }

    throw sem_exception(
            "semantics error, cannot perform operation because the types of these two values are inconsistent"
    );
}
