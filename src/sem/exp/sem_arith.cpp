#include "sem/exception/sem_exception.h"
#include "sem/exp/sem_arith.h"

const sem_type &sem::assert_can_do_arith(const sem_type &type_l, const sem_type &type_r) {
    if (!type_l.is_type && !type_r.is_type) {
        if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::INT_TYPE) {
            return built_in_type::INT_VAL;
        } else if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::REAL_TYPE) {
            return built_in_type::REAL_VAL;
        } else if (type_l == built_in_type::REAL_TYPE && type_r == built_in_type::INT_TYPE) {
            return built_in_type::REAL_VAL;
        } else if (type_l == built_in_type::REAL_TYPE && type_r == built_in_type::REAL_TYPE) {
            return built_in_type::REAL_VAL;
        }
    }

    throw sem_exception("semantics error, must be integer type values or real type values");
}

const sem_type &sem::assert_can_do_add(const sem_type &type_l, const sem_type &type_r) {
    try {
        return assert_can_do_arith(type_l, type_r);
    } catch (const sem_exception &e) {
        if (!type_l.is_type && !type_r.is_type) {
            if (type_l.ptr > 0 && type_r == built_in_type::INT_TYPE) {
                return type_l;
            }
        }

        throw sem_exception(
                "semantics error, must be one of the following\n"
                "    integer type + integer type\n"
                "    integer type + real type\n"
                "    real type + integer type\n"
                "    real type + real type\n"
                "    pointer type + integer type\n"
        );
    }
}

const sem_type &sem::assert_can_do_sub(const sem_type &type_l, const sem_type &type_r) {
    try {
        return assert_can_do_arith(type_l, type_r);
    } catch (const sem_exception &e) {
        if (!type_l.is_type && !type_r.is_type) {
            if (type_l.ptr > 0 && type_l == type_r) {
                return built_in_type::INT_VAL;
            }
        }

        throw sem_exception(
                "semantics error, must be one of the following\n"
                "    integer type - integer type\n"
                "    integer type - real type\n"
                "    real type - integer type\n"
                "    real type - real type\n"
                "    pointer type - same pointer type\n"
        );
    }
}

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
    return sem_value{true, {.num = value_l.value.num / value_r.value.num}};
}

sem_value sem::do_arith_mod(const sem_value &value_l, const sem_value &value_r) {
    return sem_value{true, {.num = value_l.value.num % value_r.value.num}};
}
