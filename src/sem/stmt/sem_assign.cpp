#include "sem/exception/sem_exception.h"
#include "sem/stmt/sem_assign.h"

void sem::assert_can_assign(ast_lhs *lhs, const sem_type &type) {
    const sem_type &t = lhs->get_type();
    if (lhs->get_value().known || t.is_type) {
        throw sem_exception("semantics error, only variables can be assigned");
    }

    if (!type.is_type) {
        if (t == type) {
            return;
        } else if (t == built_in_type::REAL_TYPE && type == built_in_type::INT_TYPE) {
            return;
        }
    }
    throw sem_exception("semantics error, cannot assign rhs to variable because their types are inconsistent");
}
