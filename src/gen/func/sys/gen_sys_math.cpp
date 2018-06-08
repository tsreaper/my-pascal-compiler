#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_all_types.h"
#include "gen/type/gen_convert.h"
#include "gen/val/gen_literal.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_math.h"

static llvm::Function *pow_func = nullptr;

llvm::Function *register_pow() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type(), gen::get_llvm_real_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_real_type(), arg_types, false
    );
    RETURN_C_FUNC("pow");
}

#define CONV_ARG llvm::Value *arg = get_converted_llvm_args({built_in_type::REAL_TYPE}, {args[0]})[0]

llvm::Value *gen::gen_sys_sqr(const std::vector<ast_value_node *> &args) {
    if (pow_func == nullptr) {
        pow_func = register_pow();
    }
    CONV_ARG;
    return ir_builder.CreateCall(pow_func, {arg, get_llvm_real(2.0)}, "call_pow");
}

#define REGISTER_REAL_C_FUNC(name) { \
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type()}; \
    llvm::FunctionType *func_type = llvm::FunctionType::get( \
        gen::get_llvm_real_type(), arg_types, false \
    ); \
    RETURN_C_FUNC(name); \
}

static llvm::Function *sqrt_func = nullptr;

llvm::Function *register_sqrt() {
    REGISTER_REAL_C_FUNC("sqrt");
}

llvm::Value *gen::gen_sys_sqrt(const std::vector<ast_value_node *> &args) {
    if (sqrt_func == nullptr) {
        sqrt_func = register_sqrt();
    }
    CONV_ARG;
    return ir_builder.CreateCall(sqrt_func, {arg}, "call_sqrt");
}

static llvm::Function *exp_func = nullptr;

llvm::Function *register_exp() {
    REGISTER_REAL_C_FUNC("exp");
}

llvm::Value *gen::gen_sys_exp(const std::vector<ast_value_node *> &args) {
    if (exp_func == nullptr) {
        exp_func = register_exp();
    }
    CONV_ARG;
    return ir_builder.CreateCall(exp_func, {arg}, "call_exp");
}

static llvm::Function *log_func = nullptr;

llvm::Function *register_log() {
    REGISTER_REAL_C_FUNC("log");
}

llvm::Value *gen::gen_sys_ln(const std::vector<ast_value_node *> &args) {
    if (log_func == nullptr) {
        log_func = register_log();
    }
    CONV_ARG;
    return ir_builder.CreateCall(log_func, {arg}, "call_log");
}

static llvm::Function *sin_func = nullptr;

llvm::Function *register_sin() {
    REGISTER_REAL_C_FUNC("sin");
}

llvm::Value *gen::gen_sys_sin(const std::vector<ast_value_node *> &args) {
    if (sin_func == nullptr) {
        sin_func = register_sin();
    }
    CONV_ARG;
    return ir_builder.CreateCall(sin_func, {arg}, "call_sin");
}

static llvm::Function *cos_func = nullptr;

llvm::Function *register_cos() {
    REGISTER_REAL_C_FUNC("cos");
}

llvm::Value *gen::gen_sys_cos(const std::vector<ast_value_node *> &args) {
    if (cos_func == nullptr) {
        cos_func = register_cos();
    }
    CONV_ARG;
    return ir_builder.CreateCall(cos_func, {arg}, "call_cos");
}

static llvm::Function *tan_func = nullptr;

llvm::Function *register_tan() {
    REGISTER_REAL_C_FUNC("tan");
}

llvm::Value *gen::gen_sys_tan(const std::vector<ast_value_node *> &args) {
    if (tan_func == nullptr) {
        tan_func = register_tan();
    }
    CONV_ARG;
    return ir_builder.CreateCall(tan_func, {arg}, "call_tan");
}

static llvm::Function *asin_func = nullptr;

llvm::Function *register_asin() {
    REGISTER_REAL_C_FUNC("asin");
}

llvm::Value *gen::gen_sys_arcsin(const std::vector<ast_value_node *> &args) {
    if (asin_func == nullptr) {
        asin_func = register_asin();
    }
    CONV_ARG;
    return ir_builder.CreateCall(asin_func, {arg}, "call_asin");
}

static llvm::Function *acos_func = nullptr;

llvm::Function *register_acos() {
    REGISTER_REAL_C_FUNC("acos");
}

llvm::Value *gen::gen_sys_arccos(const std::vector<ast_value_node *> &args) {
    if (acos_func == nullptr) {
        acos_func = register_acos();
    }
    CONV_ARG;
    return ir_builder.CreateCall(acos_func, {arg}, "call_acos");
}

static llvm::Function *atan_func = nullptr;

llvm::Function *register_atan() {
    REGISTER_REAL_C_FUNC("atan");
}

llvm::Value *gen::gen_sys_arctan(const std::vector<ast_value_node *> &args) {
    if (atan_func == nullptr) {
        atan_func = register_atan();
    }
    CONV_ARG;
    return ir_builder.CreateCall(atan_func, {arg}, "call_atan");
}
