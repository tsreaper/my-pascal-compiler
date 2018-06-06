#include "sem/type/sem_array_type.h"
#include "sem/exception/sem_exception.h"
#include "sem/stmt/sem_assign.h"

void sem::assert_can_assign(ast_value_node *lhs, const sem_type &type) {
    assert_is_variable(lhs);
    if (!can_assign(lhs->get_type(), type)) {
        throw sem_exception("semantics error, cannot assign rhs to variable because their types are inconsistent");
    }
}

bool sem::can_assign(const sem_type &type_l, const sem_type &type_r) {
    if (!type_r.is_type) {
        if (type_l == type_r) {
            return true;
        } else if (type_l == built_in_type::REAL_TYPE && type_r == built_in_type::INT_TYPE) {
            return true;
        } else if (type_l.tg == type_group::ARRAY && type_r.tg == type_group::ARRAY) {
            return array_can_assign(type_l, type_r);
        }
    }
    return false;
}

void sem::assert_is_variable(ast_value_node *val) {
    if (val->get_type().is_type || val->get_value().known) {
        throw sem_exception("semantics error, must be a variable");
    }
}
