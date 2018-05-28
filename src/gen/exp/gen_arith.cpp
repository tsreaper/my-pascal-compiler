#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/exp/gen_arith.h"

#define GEN_ARITH_OP(op, op_f, name) { \
    llvm::Value *v_l = value_l; \
    llvm::Value *v_r = value_r; \
    to_llvm_arith_type(type_l, type_r, &v_l, &v_r); \
    if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::INT_TYPE) { \
        return ir_builder.op(v_l, v_r, name); \
    } else { \
        return ir_builder.op_f(v_l, v_r, name); \
    } \
}

llvm::Value *gen::gen_arith_add(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    GEN_ARITH_OP(CreateAdd, CreateFAdd, "add_tmp");
}

llvm::Value *gen::gen_arith_sub(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    GEN_ARITH_OP(CreateSub, CreateFSub, "sub_tmp");
}

llvm::Value *gen::gen_arith_mul(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    GEN_ARITH_OP(CreateMul, CreateFMul, "mul_tmp");
}

llvm::Value *gen::gen_arith_div(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    llvm::Value *v_l = value_l;
    llvm::Value *v_r = value_r;
    to_llvm_real_type(type_l, &v_l);
    to_llvm_real_type(type_r, &v_r);
    return ir_builder.CreateFDiv(v_l, v_r, "div_tmp");
}

llvm::Value *gen::gen_arith_div_floor(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateSDiv(value_l, value_r, "div_floor_tmp");
}

llvm::Value *gen::gen_arith_mod(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateSRem(value_l, value_r, "mod_tmp");
}
