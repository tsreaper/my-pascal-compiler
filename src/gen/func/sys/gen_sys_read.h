#ifndef MPC_GEN_SYS_READ_H
#define MPC_GEN_SYS_READ_H

#include <vector>

#include "ast/val/ast_id.h"

namespace gen {
    void gen_read(std::vector<ast_id *> args);

    // void gen_readln(ast_id *arg);
}

#endif //MPC_GEN_SYS_READ_H
