#include "sem/exception/sem_exception.h"
#include "sem/func/sys/sem_all_sys_funcs.h"
#include "sem/func/sys/sem_sys_func.h"

typedef std::pair<func_sign, sem_type> func_sign_ret;
const sem_type &sem::get_sys_func_ret_type(const func_sign &sign) {
    static std::vector<func_sign_ret> sys_func = {
            {get_sys_abs_int_sign(), built_in_type::INT_TYPE},
            {get_sys_abs_real_sign(), built_in_type::REAL_TYPE}
    };

    // Matching write/writeln/read.
    if (sign.id == "write" || sign.id == "writeln") {
        assert_sys_write_args_type(sign);
        return built_in_type::VOID_TYPE;
    }
    if (sign.id == "read") {
        assert_sys_read_args_type(sign);
        return built_in_type::VOID_TYPE;
    }

    // Matching normal system function.
    for (auto &f : sys_func) {
        if (f.first == sign) {
            return f.second;
        }
    }

    throw sem_exception("semantics error, undeclared procedure/function " + sign.id);
}
