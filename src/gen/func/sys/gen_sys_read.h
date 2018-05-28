#ifndef MY_PASCAL_GEN_SYS_READ_H
#define MY_PASCAL_GEN_SYS_READ_H

#include <vector>

#include "ast/val/ast_id.h"

namespace gen {
    void gen_read(std::vector<ast_id *> args);

    // void gen_readln(ast_id *arg);
}

#endif //MY_PASCAL_GEN_SYS_READ_H
