#include <stdexcept>
#include <functional>

#include "sem/func/sys/sem_all_sys_funcs.h"
#include "gen/func/sys/gen_sys_func.h"

typedef std::pair<func_sign, std::function<llvm::Value *(const std::vector<ast_value_node *> &)>> func_sign_gen;
llvm::Value *gen::get_sys_func_call(const func_sign &sign, const std::vector<ast_value_node *> &args) {
    static std::vector<func_sign_gen> sys_func = {
            {sem::get_sys_abs_int_sign(), gen_sys_abs_int},
            {sem::get_sys_abs_real_sign(), gen_sys_abs_real},
            {sem::get_sys_arccos_sign(), gen_sys_arccos},
            {sem::get_sys_arcsin_sign(), gen_sys_arcsin},
            {sem::get_sys_arctan_sign(), gen_sys_arctan},
            {sem::get_sys_chr_sign(), gen_sys_chr},
            {sem::get_sys_copy_sign(), gen_sys_copy},
            {sem::get_sys_cos_sign(), gen_sys_cos},
            {sem::get_sys_exp_sign(), gen_sys_exp},
            {sem::get_sys_frac_sign(), gen_sys_frac},
            {sem::get_sys_ln_sign(), gen_sys_ln},
            {sem::get_sys_int_sign(), gen_sys_int},
            {sem::get_sys_min_int_sign(), gen_sys_min_int},
            {sem::get_sys_min_real_sign(), gen_sys_min_real},
            {sem::get_sys_max_int_sign(), gen_sys_max_int},
            {sem::get_sys_max_real_sign(), gen_sys_max_real},
            {sem::get_sys_ord_sign(), gen_sys_ord},
            {sem::get_sys_pred_sign(), gen_sys_pred},
            {sem::get_sys_random_sign(), gen_sys_random},
            {sem::get_sys_randomize_sign(), gen_sys_randomize},
            {sem::get_sys_round_sign(), gen_sys_round},
            {sem::get_sys_sin_sign(), gen_sys_sin},
            {sem::get_sys_sqr_sign(), gen_sys_sqr},
            {sem::get_sys_sqrt_sign(), gen_sys_sqrt},
            {sem::get_sys_succ_sign(), gen_sys_succ},
            {sem::get_sys_tan_sign(), gen_sys_tan},
            {sem::get_sys_trunc_sign(), gen_sys_trunc},
    };

    // Matching var arg functions
    if (sign.id == "write") {
        return gen_sys_write(args, false);
    } else if (sign.id == "writeln") {
        return gen_sys_write(args, true);
    } else if (sign.id == "read") {
        return gen_sys_read(args, false);
    } else if (sign.id == "readln") {
        return gen_sys_read(args, true);
    } else if (sign.id == "concat") {
        return gen_sys_concat(args);
    } else if (sign.id == "fillchar") {
        return gen_sys_fillchar(args);
    } else if (sign.id == "inc") {
        return gen_sys_inc(args);
    } else if (sign.id == "dec") {
        return gen_sys_dec(args);
    }

    // Matching normal system functions
    for (auto &f : sys_func) {
        if (f.first == sign) {
            return f.second(args);
        }
    }

    throw std::invalid_argument("[gen_func_context::get_func] Unknown procedure/function " + sign.id);
}
