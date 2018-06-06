#include <vector>
#include <stdexcept>
#include <sem/val/sem_value.h>

#include "sem/exception/sem_exception.h"
#include "sem/exp/sem_arith.h"

#define ASSERT_SAME_TYPE { \
    if (type_l != type_r) { \
        throw std::invalid_argument("[sem::ASSERT_SAME_TYPE] type_l and type_r must be the same"); \
    } \
}

#define ARITH_TYPE_TABLE static std::vector<sem_type> table = { \
    built_in_type::INT_VAL, \
    built_in_type::REAL_VAL, \
}

#define INT_ONLY_TABLE static std::vector<sem_type> table = { \
    built_in_type::INT_VAL, \
}

#define CHECK_IN_TABLE { \
    for (auto &t : table) { \
        if (type_l == t) { \
            return type_l; \
        } \
    } \
}

const sem_type &sem::assert_can_do_add(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_SAME_TYPE;
    ARITH_TYPE_TABLE;
    CHECK_IN_TABLE;
    throw sem_exception("semantics error, value type is not consistent with add operation");
}

const sem_type &sem::assert_can_do_sub(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_SAME_TYPE;
    ARITH_TYPE_TABLE;
    CHECK_IN_TABLE;
    throw sem_exception("semantics error, value type is not consistent with subtract operation");
}

const sem_type &sem::assert_can_do_mul(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_SAME_TYPE;
    ARITH_TYPE_TABLE;
    CHECK_IN_TABLE;
    throw sem_exception("semantics error, value type is not consistent with multiply operation");
}

const sem_type &sem::assert_can_do_div(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_SAME_TYPE;
    ARITH_TYPE_TABLE;
    for (auto &t : table) {
        if (type_l == t) {
            return built_in_type::REAL_VAL;
        }
    }
    throw sem_exception("semantics error, value type is not consistent with divide operation");
}

const sem_type &sem::assert_can_do_div_floor(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_SAME_TYPE;
    INT_ONLY_TABLE;
    CHECK_IN_TABLE;
    throw sem_exception("semantics error, value type is not consistent with divide (floor) operation");
}

const sem_type &sem::assert_can_do_mod(const sem_type &type_l, const sem_type &type_r) {
    ASSERT_SAME_TYPE;
    INT_ONLY_TABLE;
    CHECK_IN_TABLE;
    throw sem_exception("semantics error, value type is not consistent with mod operation");
}

#define DO_ARITH_OP(op) { \
    if (type_l == built_in_type::INT_VAL) { \
        return sem_value{true, {.num = value_l.value.num op value_r.value.num}}; \
    } else if (type_l == built_in_type::REAL_VAL) { \
        return sem_value{true, {.real = value_l.value.real op value_r.value.real}}; \
    } \
    throw std::invalid_argument("[sem::DO_ARITH_OP] Invalid operand type"); \
}

#define DO_INT_ONLY_OP(op) { \
    if (type_l == built_in_type::INT_VAL) { \
        return sem_value{true, {.num = value_l.value.num op value_r.value.num}}; \
    } \
    throw std::invalid_argument("[sem::DO_INT_ONLY_OP] Invalid operand type"); \
}

sem_value sem::do_arith_add(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_ARITH_OP(+);
}

sem_value sem::do_arith_sub(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_ARITH_OP(-);
}

sem_value sem::do_arith_mul(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_ARITH_OP(*);
}

sem_value sem::do_arith_div(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    if (type_l == built_in_type::INT_VAL) {
        return sem_value{true, {.real = 1.0 * value_l.value.num / value_r.value.num}};
    } else if (type_l == built_in_type::REAL_VAL) {
        return sem_value{true, {.real = value_l.value.real / value_r.value.real}};
    }
    throw std::invalid_argument("[sem::DO_ARITH_OP] Invalid operand type");
}

sem_value sem::do_arith_div_floor(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_INT_ONLY_OP(/);
}

sem_value sem::do_arith_mod(
        const sem_type &type_l, const sem_type &type_r, const sem_value &value_l, const sem_value &value_r
) {
    ASSERT_SAME_TYPE;
    DO_INT_ONLY_OP(%);
}
