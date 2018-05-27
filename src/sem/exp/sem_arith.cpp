#include "sem/exception/sem_exception.h"
#include "sem/exp/sem_arith.h"

#define DO_ARITH_OP(op) { \
    if (type_l == built_in_type::INT_VAL && type_r == built_in_type::INT_VAL) { \
        return sem_value{true, {.num = value_l.value.num op value_r.value.num}}; \
    } else if (type_l == built_in_type::REAL_VAL && type_r == built_in_type::INT_VAL) { \
        return sem_value{true, {.real = value_l.value.real op value_r.value.num}}; \
    } else if (type_l == built_in_type::INT_VAL && type_r == built_in_type::REAL_VAL) { \
        return sem_value{true, {.real = value_l.value.num op value_r.value.real}}; \
    } else { \
        return sem_value{true, {.real = value_l.value.real op value_r.value.real}}; \
    } \
}

sem_value sem::do_arith_add(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_ARITH_OP(+);
}

sem_value sem::do_arith_sub(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_ARITH_OP(-);
}

sem_value sem::do_arith_mul(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_ARITH_OP(*);
}

sem_value sem::do_arith_div(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::INT_TYPE) {
        return sem_value{true, {.real = 1.0 * value_l.value.num / value_r.value.num}};
    } else if (type_l == built_in_type::REAL_VAL && type_r == built_in_type::INT_TYPE) {
        return sem_value{true, {.real = value_l.value.real / value_r.value.num}};
    } else if (type_l == built_in_type::INT_VAL && type_r == built_in_type::REAL_TYPE) {
        return sem_value{true, {.real = value_l.value.num / value_r.value.real}};
    } else {
        return sem_value{true, {.real = value_l.value.real / value_r.value.real}};
    }
}

sem_value sem::do_arith_div_floor(const sem_value &value_l, const sem_value &value_r) {
    if (value_r.value.num == 0) {
        throw sem_exception("semantics error, cannot div zero");
    }
    return sem_value{true, {.num = value_l.value.num / value_r.value.num}};
}

sem_value sem::do_arith_mod(const sem_value &value_l, const sem_value &value_r) {
    if (value_r.value.num == 0) {
        throw sem_exception("semantics error, cannot mod zero");
    }
    return sem_value{true, {.num = value_l.value.num % value_r.value.num}};
}
