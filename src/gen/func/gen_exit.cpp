#include "sem/sem.h"
#include "sem/func/sem_func.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "gen/func/gen_func.h"
#include "gen/func/gen_exit.h"

void gen::gen_exit(llvm::Value *ret_val) {
    if (ret_val != nullptr) {
        ir_builder.CreateRet(ret_val);
    } else {
        // No return value specified. Use default value
        if (sem_env.is_global()) {
            ir_builder.CreateRet(get_llvm_int(0));
        } else {
            const func_sign &sign = sem::get_current_func_sign();
            const sem_type &ret_type = sem::get_ret_type(sign);
            if (ret_type != built_in_type::VOID_TYPE) {
                llvm::Value *ret = ir_builder.CreateLoad(gen::get_mem(sign.id), "ret");
                ir_builder.CreateRet(ret);
            } else {
                ir_builder.CreateRetVoid();
            }
        }
    }
}
