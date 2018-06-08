#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/exp/gen_cmp.h"
#include "gen/type/gen_all_types.h"
#include "gen/type/gen_convert.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_min_max.h"

static llvm::Function *min_int_func = nullptr, *max_int_func = nullptr;
static llvm::Function *min_real_func = nullptr, *max_real_func = nullptr;

#define REGISTER_MIN_MAX_INT(name, cmp) { \
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_int_type(), gen::get_llvm_int_type()}; \
    llvm::FunctionType *func_type = llvm::FunctionType::get( \
        gen::get_llvm_int_type(), arg_types, false \
    ); \
    llvm::Function *func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, name, &llvm_module); \
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(llvm_context, "entry", func); \
    llvm::BasicBlock *old_bb = ir_builder.GetInsertBlock(); \
    ir_builder.SetInsertPoint(bb); \
 \
    llvm::BasicBlock *a_bb = llvm::BasicBlock::Create(llvm_context, name"_a", func); \
    llvm::BasicBlock *b_bb = llvm::BasicBlock::Create(llvm_context, name"_b", func); \
    auto arg_it = func->arg_begin(); \
    ir_builder.CreateCondBr(cmp(built_in_type::INT_TYPE, arg_it, arg_it + 1), a_bb, b_bb); \
    ir_builder.SetInsertPoint(a_bb); \
 \
    ir_builder.CreateRet(arg_it); \
    ir_builder.SetInsertPoint(b_bb); \
 \
    ir_builder.CreateRet(arg_it + 1); \
    ir_builder.SetInsertPoint(old_bb); \
 \
    return func; \
}

llvm::Function *register_min_int() {
    REGISTER_MIN_MAX_INT("min", gen::gen_cmp_lt);
}

llvm::Value *gen::gen_sys_min_int(const std::vector<ast_value_node *> &args) {
    return gen_sys_min_int_impl(args[0]->get_llvm_value(), args[1]->get_llvm_value());
}

llvm::Value *gen::gen_sys_min_int_impl(llvm::Value *a, llvm::Value *b) {
    if (min_int_func == nullptr) {
        min_int_func = register_min_int();
    }
    return ir_builder.CreateCall(min_int_func, {a, b}, "call_min_int");
}

llvm::Function *register_max_int() {
    REGISTER_MIN_MAX_INT("max", gen::gen_cmp_gt);
}

llvm::Value *gen::gen_sys_max_int(const std::vector<ast_value_node *> &args) {
    return gen_sys_max_int_impl(args[0]->get_llvm_value(), args[1]->get_llvm_value());
}

llvm::Value *gen::gen_sys_max_int_impl(llvm::Value *a, llvm::Value *b) {
    if (max_int_func == nullptr) {
        max_int_func = register_max_int();
    }
    return ir_builder.CreateCall(max_int_func, {a, b}, "call_max_int");
}

llvm::Function *register_min_real() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type(), gen::get_llvm_real_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_real_type(), arg_types, false
    );
    RETURN_C_FUNC("fmin");
}

#define CONV_ARGS const std::vector<llvm::Value *> &conv_args = get_converted_llvm_args( \
    {built_in_type::REAL_TYPE, built_in_type::REAL_TYPE}, args \
)

llvm::Value *gen::gen_sys_min_real(const std::vector<ast_value_node *> &args) {
    CONV_ARGS;
    return gen_sys_min_real_impl(conv_args[0], conv_args[1]);
}

llvm::Value *gen::gen_sys_min_real_impl(llvm::Value *a, llvm::Value *b) {
    if (min_real_func == nullptr) {
        min_real_func = register_min_real();
    }
    return ir_builder.CreateCall(min_real_func, {a, b}, "call_min_real");
}

llvm::Function *register_max_real() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type(), gen::get_llvm_real_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_real_type(), arg_types, false
    );
    RETURN_C_FUNC("fmax");
}

llvm::Value *gen::gen_sys_max_real(const std::vector<ast_value_node *> &args) {
    CONV_ARGS;
    return gen_sys_max_real_impl(conv_args[0], conv_args[1]);
}

llvm::Value *gen::gen_sys_max_real_impl(llvm::Value *a, llvm::Value *b) {
    if (max_real_func == nullptr) {
        max_real_func = register_max_real();
    }
    return ir_builder.CreateCall(max_real_func, {a, b}, "call_max_real");
}
