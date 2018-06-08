#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_all_types.h"
#include "gen/type/gen_convert.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen_sys_real_int_func.h"

static llvm::Function *modf_func = nullptr, *trunc_func = nullptr, *round_func = nullptr;

llvm::Function *register_modf() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type(), gen::get_llvm_real_ptr_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_real_type(), arg_types, false
    );
    RETURN_C_FUNC("modf");
}

#define CONV_ARG llvm::Value *arg = get_converted_llvm_args({built_in_type::REAL_TYPE}, {args[0]})[0]

llvm::Value *gen::gen_sys_int(const std::vector<ast_value_node *> &args) {
    if (modf_func == nullptr) {
        modf_func = register_modf();
    }
    CONV_ARG;
    llvm::Value *int_mem = ir_builder.CreateAlloca(get_llvm_real_type(), nullptr, "modf_int");
    ir_builder.CreateCall(modf_func, {arg, int_mem}, "call_modf");
    return ir_builder.CreateLoad(int_mem, "load_modf_int");
}

llvm::Value *gen::gen_sys_frac(const std::vector<ast_value_node *> &args) {
    if (modf_func == nullptr) {
        modf_func = register_modf();
    }
    CONV_ARG;
    llvm::Value *int_mem = ir_builder.CreateAlloca(get_llvm_real_type(), nullptr, "modf_int");
    return ir_builder.CreateCall(modf_func, {arg, int_mem}, "call_modf");
}

llvm::Function *register_trunc() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_real_type(), arg_types, false
    );
    RETURN_C_FUNC("trunc");
}

llvm::Value *gen::gen_sys_trunc(const std::vector<ast_value_node *> &args) {
    if (trunc_func == nullptr) {
        trunc_func = register_trunc();
    }
    CONV_ARG;
    llvm::Value *trunc_real = ir_builder.CreateCall(trunc_func, {arg}, "call_trunc");
    return ir_builder.CreateFPToSI(trunc_real, get_llvm_int_type(), "f2i");
}

llvm::Function *register_round() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_real_type(), arg_types, false
    );
    RETURN_C_FUNC("round");
}

llvm::Value *gen::gen_sys_round(const std::vector<ast_value_node *> &args) {
    if (round_func == nullptr) {
        round_func = register_round();
    }
    CONV_ARG;
    llvm::Value *round_real = ir_builder.CreateCall(round_func, {arg}, "call_round");
    return ir_builder.CreateFPToSI(round_real, get_llvm_int_type(), "f2i");
}
