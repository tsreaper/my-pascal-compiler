#ifndef MPC_SEM_ASSIGN_H
#define MPC_SEM_ASSIGN_H

#include <string>

#include "ast/val/ast_lhs.h"
#include "sem/type/sem_type.h"

namespace sem {
    void assert_can_assign(ast_lhs *lhs, const sem_type &type);
}

#endif //MPC_SEM_ASSIGN_H
