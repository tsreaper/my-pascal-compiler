#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_all_sys_funcs.h"
#include "sem/func/sys/sem_sys_func.h"

const func_sign_ret &sem::get_sys_call_func_sign_ret(const func_sign &sign) {
    static std::vector<func_sign_ret> sys_func = {
            {get_sys_abs_int_sign(), built_in_type::INT_TYPE},
            {get_sys_abs_real_sign(), built_in_type::REAL_TYPE},
            {get_sys_copy_sign(), non_built_in_type::STR_TYPE},
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
            return f;
        }
    }

    throw sem_exception("semantics error, undeclared procedure/function " + sign.id);
}
