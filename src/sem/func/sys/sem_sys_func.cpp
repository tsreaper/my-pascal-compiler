#include <functional>

#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_all_sys_funcs.h"
#include "sem/func/sys/sem_sys_func.h"

func_sign_ret sem::get_sys_call_func_sign_ret(const func_sign &sign) {
    static std::vector<std::pair<func_sign, std::function<sem_type (const func_sign &)>>> sys_func = {
            {get_sys_abs_int_sign(), get_sys_abs_int_ret},
            {get_sys_abs_real_sign(), get_sys_abs_real_ret},
            {get_sys_copy_sign(), get_sys_copy_ret},
    };

    // Matching write/writeln/read.
    if (sign.id == "write") {
        static func_sign_ret ret = {{"write", {}}, built_in_type::VOID_TYPE};
        assert_sys_write_args_type(sign);
        return ret;
    } else if (sign.id == "writeln") {
        static func_sign_ret ret = {{"writeln", {}}, built_in_type::VOID_TYPE};
        assert_sys_write_args_type(sign);
        return ret;
    } else if (sign.id == "read") {
        static func_sign_ret ret = {{"read", {}}, built_in_type::VOID_TYPE};
        assert_sys_read_args_type(sign);
        return ret;
    } else if (sign.id == "readln") {
        static func_sign_ret ret = {{"readln", {}}, built_in_type::VOID_TYPE};
        assert_sys_read_args_type(sign);
        return ret;
    }

    // Matching normal system function.
    for (auto &f : sys_func) {
        if (f.first.can_be_called(sign)) {
            return {f.first, f.second(sign)};
        }
    }

    throw sem_exception("semantics error, undeclared procedure/function " + sign.id);
}
