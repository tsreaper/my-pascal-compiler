#ifndef MPC_GEN_LOOP_H
#define MPC_GEN_LOOP_H

#include <vector>

#include "ast/stmt/loop/ast_loop.h"

class gen_loop_context {
public:
    void push(ast_loop *loop);

    void pop();

    ast_loop *get_current_loop() const;

private:
    std::vector<ast_loop *> loop_vec;
};

namespace gen {
    ast_loop *get_current_loop();
}

#endif //MPC_GEN_LOOP_H
