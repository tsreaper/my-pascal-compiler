#ifndef MPC_GEN_SYS_READ_H
#define MPC_GEN_SYS_READ_H

#include <vector>

#include "ast/val/ast_lhs.h"

namespace gen {
    void gen_read(std::vector<ast_lhs *> args);

    // void gen_readln(ast_id *arg);
}

#endif //MPC_GEN_SYS_READ_H
