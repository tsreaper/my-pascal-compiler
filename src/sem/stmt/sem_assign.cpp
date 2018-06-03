#include "sem/exception/sem_exception.h"
#include "sem/stmt/sem_assign.h"

void sem::assert_can_assign(ast_value_node *lhs, const sem_type &type) {
    assert_is_variable(lhs);

    if (!type.is_type) {
        const sem_type &t = lhs->get_type();
        if (t == type) {
            return;
        } else if (t == built_in_type::REAL_TYPE && type == built_in_type::INT_TYPE) {
            return;
        }
    }
    throw sem_exception("semantics error, cannot assign rhs to variable because their types are inconsistent");
}

void sem::assert_is_variable(ast_value_node *val) {
    if (val->get_type().is_type || val->get_value().known) {
        throw sem_exception("semantics error, must be a variable");
    }
}
