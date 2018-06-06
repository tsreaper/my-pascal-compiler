#include "sem/sem.h"
#include "sem/func/sys/sem_sys_func.h"
#include "sem/exception/sem_exception.h"
#include "sem/func/sem_call.h"

const func_sign_ret &sem::get_call_func_sign_ret(const func_sign &call_sign) {
    try {
        return sem_env.get_func_env().get_call_func_sign_ret(call_sign);
    } catch (const sem_exception &e) {
        return get_sys_call_func_sign_ret(call_sign);
    }
}
