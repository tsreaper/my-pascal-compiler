#include <functional>

#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_all_sys_funcs.h"
#include "sem/func/sys/sem_sys_func.h"

func_sign_ret sem::get_sys_call_func_sign_ret(const func_sign &sign) {
    static std::vector<std::pair<func_sign, std::function<const sem_type &(const func_sign &)>>> sys_func = {
            {get_sys_abs_int_sign(), get_sys_abs_int_ret},
            {get_sys_abs_real_sign(), get_sys_abs_real_ret},
            {get_sys_copy_sign(), get_sys_copy_ret},
    };

    // Matching var arg function
    if (sign.id == "write") {
        assert_sys_write_args_type(sign);
        return {{"write", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "writeln") {
        assert_sys_write_args_type(sign);
        return {{"writeln", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "read") {
        assert_sys_read_args_type(sign);
        return {{"read", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "readln") {
        assert_sys_read_args_type(sign);
        return {{"readln", {}}, built_in_type::VOID_TYPE};
    } else if (sign.id == "concat") {
        assert_sys_concat_args_type(sign);
        return {{"concat", {}}, get_sys_concat_ret(sign)};
    }

    // Matching normal system function
    for (auto &f : sys_func) {
        if (f.first.can_be_called(sign)) {
            return {f.first, f.second(sign)};
        }
    }

    throw sem_exception("semantics error, undeclared procedure/function " + sign.id);
}
