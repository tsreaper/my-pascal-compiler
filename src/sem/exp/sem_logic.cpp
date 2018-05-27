#include "sem/exp/sem_logic.h"

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
