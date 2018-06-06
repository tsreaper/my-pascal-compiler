#include "sem/exception/sem_exception.h"
#include "sem/exp/sem_logic.h"

void sem::assert_can_do_logic(const sem_type &type_l, const sem_type &type_r) {
    if (!type_l.is_type && !type_r.is_type) {
        if (type_l == built_in_type::BOOL_TYPE && type_r == built_in_type::BOOL_TYPE) {
            return;
        }
    }

    throw sem_exception("semantics error, must be boolean type values");
}

#define DO_LOGIC_OP(op) return sem_value{true, {.boo = value_l.value.boo op value_r.value.boo }}

sem_value sem::do_logic_and(const sem_value &value_l, const sem_value &value_r) {
    DO_LOGIC_OP(&&);
}

sem_value sem::do_logic_or(const sem_value &value_l, const sem_value &value_r) {
    DO_LOGIC_OP(||);
}

sem_value sem::do_logic_xor(const sem_value &value_l, const sem_value &value_r) {
    DO_LOGIC_OP(^);
}

sem_value sem::do_logic_not(const sem_value &value) {
    return sem_value{true, {.boo = !value.value.boo}};
}
