#include <functional>

#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_all_sys_funcs.h"
#include "sem/func/sys/sem_sys_func.h"

func_sign_ret sem::get_sys_call_func_sign_ret(const func_sign &sign, const std::vector<bool> &rval_vec) {
    static std::vector<std::pair<func_sign, std::function<const sem_type &(const func_sign &)>>> sys_func = {
            {get_sys_abs_int_sign(), get_sys_abs_int_ret},
            {get_sys_abs_real_sign(), get_sys_abs_real_ret},
            {get_sys_arccos_sign(), get_sys_arccos_ret},
            {get_sys_arcsin_sign(), get_sys_arcsin_ret},
            {get_sys_arctan_sign(), get_sys_arctan_ret},
            {get_sys_chr_sign(), get_sys_chr_ret},
            {get_sys_copy_sign(), get_sys_copy_ret},
            {get_sys_cos_sign(), get_sys_cos_ret},
            {get_sys_exp_sign(), get_sys_exp_ret},
            {get_sys_frac_sign(), get_sys_frac_ret},
            {get_sys_ln_sign(), get_sys_ln_ret},
            {get_sys_int_sign(), get_sys_int_ret},
            {get_sys_min_int_sign(), get_sys_min_int_ret},
            {get_sys_min_real_sign(), get_sys_min_real_ret},
            {get_sys_max_int_sign(), get_sys_max_int_ret},
            {get_sys_max_real_sign(), get_sys_max_real_ret},
            {get_sys_ord_sign(), get_sys_ord_ret},
            {get_sys_pred_sign(), get_sys_pred_ret},
            {get_sys_random_sign(), get_sys_random_ret},
            {get_sys_randomize_sign(), get_sys_randomize_ret},
            {get_sys_round_sign(), get_sys_round_ret},
            {get_sys_sin_sign(), get_sys_sin_ret},
            {get_sys_sqr_sign(), get_sys_sqr_ret},
            {get_sys_sqrt_sign(), get_sys_sqrt_ret},
            {get_sys_succ_sign(), get_sys_succ_ret},
            {get_sys_tan_sign(), get_sys_tan_ret},
            {get_sys_trunc_sign(), get_sys_trunc_ret},
    };

    // Matching var arg function
    if (sign.id == "write") {
        assert_sys_write_args_type(sign);
        return {{"write", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "writeln") {
        assert_sys_write_args_type(sign);
        return {{"writeln", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "read") {
        assert_sys_read_args_type(sign, rval_vec);
        return {{"read", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "readln") {
        assert_sys_read_args_type(sign, rval_vec);
        return {{"readln", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "concat") {
        assert_sys_concat_args_type(sign);
        return {{"concat", {}}, get_sys_concat_ret(sign)};
    } else if (sign.id == "fillchar") {
        assert_sys_fillchar_args_type(sign, rval_vec);
        return {{"fillchar", sign.param_type_vec}, built_in_type::VOID_TYPE};
    } else if (sign.id == "inc") {
        assert_sys_inc_dec_args_type(sign, rval_vec);
        return {{"inc", sign.param_type_vec}, built_in_type::VOID_TYPE};
    } else if (sign.id == "dec") {
        assert_sys_inc_dec_args_type(sign, rval_vec);
        return {{"dec", sign.param_type_vec}, built_in_type::VOID_TYPE};
    }

    // Matching normal system function
    for (auto &f : sys_func) {
        if (f.first.can_be_called(sign)) {
            return {f.first, f.second(sign)};
        }
    }

    throw sem_exception("semantics error, undeclared procedure/function " + sign.id);
}
