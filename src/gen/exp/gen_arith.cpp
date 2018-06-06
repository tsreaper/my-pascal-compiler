#include <stdexcept>

#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "gen/type/gen_type.h"
#include "gen/exp/gen_arith.h"

#define GEN_ARITH_OP(op, op_f, name) { \
    if (type == built_in_type::REAL_TYPE) { \
        return ir_builder.op_f(value_l, value_r, name); \
    } else { \
        return ir_builder.op(value_l, value_r, name); \
    } \
}

llvm::Value *gen::gen_arith_add(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    GEN_ARITH_OP(CreateAdd, CreateFAdd, "add_tmp");
}

llvm::Value *gen::gen_arith_sub(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    GEN_ARITH_OP(CreateSub, CreateFSub, "sub_tmp");
}

llvm::Value *gen::gen_arith_mul(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    GEN_ARITH_OP(CreateMul, CreateFMul, "mul_tmp");
}

llvm::Value *gen::gen_arith_div(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateFDiv(value_l, value_r, "div_tmp");
}

llvm::Value *gen::gen_arith_div_floor(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateSDiv(value_l, value_r, "div_floor_tmp");
}

llvm::Value *gen::gen_arith_mod(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateSRem(value_l, value_r, "mod_tmp");
}

llvm::Value *gen::gen_arith_add_one(const sem_type &type, llvm::Value *value) {
    if (type == built_in_type::INT_TYPE) {
        return ir_builder.CreateAdd(value, get_llvm_int(sem_value{true, {.num = 1}}));
    } else if (type == built_in_type::CHAR_TYPE) {
        return ir_builder.CreateAdd(value, get_llvm_char(sem_value{true, {.chr = 1}}));
    } else if (type.tg == type_group::ENUM) {
        return ir_builder.CreateAdd(value, get_llvm_int(sem_value{true, {.num = 1}}));
    }
    throw std::invalid_argument("[gen::gen_arith_add_one] Invalid operand type");
}

llvm::Value *gen::gen_arith_sub_one(const sem_type &type, llvm::Value *value) {
    if (type == built_in_type::INT_TYPE) {
        return ir_builder.CreateSub(value, get_llvm_int(sem_value{true, {.num = 1}}));
    } else if (type == built_in_type::CHAR_TYPE) {
        return ir_builder.CreateSub(value, get_llvm_char(sem_value{true, {.chr = 1}}));
    } else if (type.tg == type_group::ENUM) {
        return ir_builder.CreateSub(value, get_llvm_int(sem_value{true, {.num = 1}}));
    }
    throw std::invalid_argument("[gen::gen_arith_add_one] Invalid operand type");
}
