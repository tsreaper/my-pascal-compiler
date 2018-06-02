#include "sem/exception/sem_exception.h"
#include "sem/exp/sem_cmp.h"

const sem_type &sem::assert_can_equal(const sem_type &type_l, const sem_type &type_r) {
    if (!type_l.is_type && !type_r.is_type) {
        if (
                (type_l == built_in_type::INT_TYPE || type_l == built_in_type::REAL_TYPE) &&
                (type_r == built_in_type::INT_TYPE || type_r == built_in_type::REAL_TYPE)
                ) {
            return built_in_type::BOOL_VAL;
        }
        if (type_l != built_in_type::VOID_TYPE && type_l == type_r) {
            return built_in_type::BOOL_VAL;
        }
    }

    throw sem_exception(
            "semantics error, cannot check the equality of these two values because their types are inconsistent"
    );
}

const sem_type &sem::assert_can_compare(const sem_type &type_l, const sem_type &type_r) {
    if (!type_l.is_type && !type_r.is_type) {
        if (
                (type_l == built_in_type::INT_TYPE || type_l == built_in_type::REAL_TYPE) &&
                (type_r == built_in_type::INT_TYPE || type_r == built_in_type::REAL_TYPE)
                ) {
            return built_in_type::BOOL_VAL;
        }
        if (type_l == built_in_type::CHAR_TYPE && type_r == built_in_type::CHAR_TYPE) {
            return built_in_type::BOOL_VAL;
        }
        if (type_l.tg == type_group::ENUM && type_l == type_r) {
            return built_in_type::BOOL_VAL;
        }
    }

    throw sem_exception("semantics error, cannot compare these two values");
}

#define DO_CMP_OP(op) { \
    if (type_l == built_in_type::INT_VAL && type_r == built_in_type::INT_VAL) { \
        return sem_value{true, {.boo = value_l.value.num op value_r.value.num}}; \
    } else if (type_l == built_in_type::REAL_VAL && type_r == built_in_type::INT_VAL) { \
        return sem_value{true, {.boo = value_l.value.real op value_r.value.num}}; \
    } else if (type_l == built_in_type::INT_VAL && type_r == built_in_type::REAL_VAL) { \
        return sem_value{true, {.boo = value_l.value.num op value_r.value.real}}; \
    } else if (type_l == built_in_type::REAL_VAL && type_r == built_in_type::REAL_VAL) { \
        return sem_value{true, {.boo = value_l.value.real op value_r.value.real}}; \
    } else if (type_l == built_in_type::CHAR_VAL) { \
        return sem_value{true, {.boo = value_l.value.chr op value_r.value.chr}}; \
    } else if (type_l == built_in_type::BOOL_VAL) { \
        return sem_value{true, {.boo = value_l.value.boo op value_r.value.boo}}; \
    } else { \
        return sem_value{false}; \
    } \
}

sem_value sem::do_cmp_eq(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_CMP_OP(==);
}

sem_value sem::do_cmp_ne(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_CMP_OP(!=);
}

sem_value sem::do_cmp_lt(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_CMP_OP(<);
}

sem_value sem::do_cmp_gt(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_CMP_OP(>);
}

sem_value sem::do_cmp_le(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_CMP_OP(<=);
}

sem_value sem::do_cmp_ge(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    DO_CMP_OP(>=);
}
