#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/type/gen_convert.h"
#include "gen/func/gen_func.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/gen_call.h"

llvm::Value *gen::get_func_call(const func_sign &sign, const std::vector<ast_value_node *> &args) {
    llvm::Function *func;
    try {
        func = get_func(sign);
    } catch (const std::invalid_argument &e) {
        return get_sys_func_call(sign, args);
    }

    const std::vector<llvm::Value *> &args_vec = get_converted_llvm_args(sign.param_type_vec, args);
    const sem_type &ret_type = sem::get_ret_type(sign);
    if (ret_type == built_in_type::VOID_TYPE) {
        return ir_builder.CreateCall(func, args_vec);
    } else {
        return ir_builder.CreateCall(func, args_vec, "call_" + sign.id);
    }
}

std::vector<llvm::Value *> gen::get_converted_llvm_args(
        const std::vector<sem_type> &dest_type_vec, const std::vector<ast_value_node *> &node_vec
) {
    std::vector<llvm::Value *> ret;
    for (int i = 0; i < node_vec.size(); i++) {
        ret.emplace_back(llvm_type_convert(
                node_vec[i]->get_type(), dest_type_vec[i], node_vec[i]->get_llvm_value()
        ));
    }
    return ret;
}
