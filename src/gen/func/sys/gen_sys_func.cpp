#include <stdexcept>
#include <functional>

#include "sem/func/sys/sem_all_sys_funcs.h"
#include "gen/func/sys/gen_sys_func.h"

typedef std::pair<func_sign, std::function<llvm::Value *(const std::vector<ast_value_node *> &)>> func_sign_gen;
llvm::Value *gen::get_sys_func_call(const func_sign &sign, const std::vector<ast_value_node *> &args) {
    static std::vector<func_sign_gen> sys_func = {
            {sem::get_sys_abs_int_sign(), gen_sys_abs_int},
            {sem::get_sys_abs_real_sign(), gen_sys_abs_real},
            {sem::get_sys_copy_sign(), gen_sys_copy},
    };

    // Matching write/writeln/read.
    if (sign.id == "write") {
        return gen_sys_write(args, false);
    } else if (sign.id == "writeln") {
        return gen_sys_write(args, true);
    } else if (sign.id == "read") {
        return gen_sys_read(args, false);
    } else if (sign.id == "readln") {
        return gen_sys_read(args, true);
    }

    // Matching normal system functions.
    for (auto &f : sys_func) {
        if (f.first == sign) {
            return f.second(args);
        }
    }

    throw std::invalid_argument("[gen_func_context::get_func] Unknown procedure/function " + sign.id);
}
