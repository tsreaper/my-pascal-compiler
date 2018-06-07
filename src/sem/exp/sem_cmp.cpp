#include <vector>

#include "sem/exception/sem_exception.h"
#include "sem/exp/sem_cmp.h"

#define ASSERT_NOT_TYPE { \
    if (type_l.is_type || type_r.is_type) { \
        throw sem_exception("semantics error, must be two values"); \
    } \
}

#define CHECK_IN_TABLE { \
    for (auto &t : table) { \
        if (t == type_l) { \
            return built_in_type::BOOL_VAL; \
        } \
    } \
}

const sem_type &sem::assert_can_equal(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_NOT_TYPE;

    // Two string type?
    if (type_l.tg == type_group::STR && type_r.tg == type_group::STR) {
        return built_in_type::BOOL_VAL;
    }

    if (type_l != type_r) {
        throw sem_exception("semantics error, cannot check the equality of the values");
    }

    if (type_l.tg == type_group::ENUM) {
        return built_in_type::BOOL_VAL;
    }

    static std::vector<sem_type> table = {
            built_in_type::INT_VAL,
            built_in_type::REAL_VAL,
            built_in_type::CHAR_VAL,
            built_in_type::BOOL_VAL,
    };
    CHECK_IN_TABLE;
    throw sem_exception("semantics error, cannot check the equality of the values");
}

const sem_type &sem::assert_can_compare(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_NOT_TYPE;
    if (type_l != type_r) {
        throw sem_exception("semantics error, cannot check the equality of the values");
    }

    // Two string type?
    if (type_l.tg == type_group::STR && type_r.tg == type_group::STR) {
        return built_in_type::BOOL_VAL;
    }

    if (type_l.tg == type_group::ENUM) {
        return built_in_type::BOOL_VAL;
    }

    static std::vector<sem_type> table = {
            built_in_type::INT_VAL,
            built_in_type::REAL_VAL,
            built_in_type::CHAR_VAL,
    };
    CHECK_IN_TABLE;
    throw sem_exception("semantics error, cannot check the equality of the values");
}

#define ASSERT_SAME_TYPE { \
    if (type_l != type_r) { \
        throw std::invalid_argument("[sem::ASSERT_SAME_TYPE] type_l and type_r must be the same"); \
    } \
}

#define DO_CMP_OP(op) { \
    if (type_l == built_in_type::INT_VAL) { \
        return sem_value{true, {.boo = value_l.value.num op value_r.value.num}}; \
    } else if (type_l == built_in_type::REAL_VAL) { \
        return sem_value{true, {.boo = value_l.value.real op value_r.value.real}}; \
    } else if (type_l == built_in_type::CHAR_VAL) { \
        return sem_value{true, {.boo = value_l.value.chr op value_r.value.chr}}; \
    } else if (type_l == built_in_type::BOOL_VAL) { \
        return sem_value{true, {.boo = value_l.value.boo op value_r.value.boo}}; \
    } else if (type_l.tg == type_group::ENUM) { \
        return sem_value{true, {.boo = value_l.value.num op value_r.value.num}}; \
    } else { \
        return sem_value{false}; \
    } \
}

sem_value sem::do_cmp_eq(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_CMP_OP(==);
}

sem_value sem::do_cmp_ne(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_CMP_OP(!=);
}

sem_value sem::do_cmp_lt(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_CMP_OP(<);
}

sem_value sem::do_cmp_gt(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_CMP_OP(>);
}

sem_value sem::do_cmp_le(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_CMP_OP(<=);
}

sem_value sem::do_cmp_ge(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_CMP_OP(>=);
}
