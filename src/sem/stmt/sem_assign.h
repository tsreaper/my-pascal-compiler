#ifndef MPC_SEM_ASSIGN_H
#define MPC_SEM_ASSIGN_H

#include <string>

#include "ast/ast_node.h"
#include "sem/type/sem_type.h"

namespace sem {
    void assert_can_assign(ast_value_node *lhs, const sem_type &type);

    bool can_assign(const sem_type &type_l, const sem_type &type_r);

    void assert_is_variable(ast_value_node *val);
}

#endif //MPC_SEM_ASSIGN_H
