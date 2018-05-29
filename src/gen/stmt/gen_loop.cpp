#include "gen/gen.h"
#include "gen/stmt/gen_loop.h"

void gen_loop_context::push(ast_loop *loop) {
    loop_vec.emplace_back(loop);
}

void gen_loop_context::pop() {
    loop_vec.pop_back();
}

ast_loop *gen_loop_context::get_current_loop() const {
    return *loop_vec.rbegin();
}

ast_loop *gen::get_current_loop() {
    return gen_env.get_loop_env().get_current_loop();
}
