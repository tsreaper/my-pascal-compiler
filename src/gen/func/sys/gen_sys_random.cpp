#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/exp/gen_arith.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_random.h"

static llvm::Function *rand_func = nullptr, *srand_func = nullptr, *time_func = nullptr;

llvm::Function *register_rand() {
    std::vector<llvm::Type *> arg_types = {};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_int_type(), arg_types, false
    );
    RETURN_C_FUNC("rand");
}

llvm::Value *gen::gen_sys_random(const std::vector<ast_value_node *> &args) {
    if (rand_func == nullptr) {
        rand_func = register_rand();
    }

    llvm::Value *llvm_rand = ir_builder.CreateCall(rand_func, {}, "call_rand");
    return gen_arith_mod(llvm_rand, args[0]->get_llvm_value());
}

llvm::Function *register_srand() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_int_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_void_type(), arg_types, false
    );
    RETURN_C_FUNC("srand");
}

llvm::Function *register_time() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_char_ptr_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_int_type(), arg_types, false
    );
    RETURN_C_FUNC("time");
}

llvm::Value *gen::gen_sys_randomize(const std::vector<ast_value_node *> &args) {
    if (srand_func == nullptr) {
        srand_func = register_srand();
        time_func = register_time();
    }

    llvm::Value *llvm_time = ir_builder.CreateCall(
            time_func, {llvm::ConstantPointerNull::get(get_llvm_char_ptr_type())}, "call_time"
    );
    return ir_builder.CreateCall(srand_func, {llvm_time});
}
