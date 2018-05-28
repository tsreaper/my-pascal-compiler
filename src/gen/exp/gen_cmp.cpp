#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/exp/gen_logic.h"
#include "gen/exp/gen_cmp.h"

llvm::Value *gen::gen_cmp_eq(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    if (type_l == built_in_type::INT_TYPE || type_l == built_in_type::REAL_TYPE) {
        llvm::Value *v_l = value_l;
        llvm::Value *v_r = value_r;
        to_llvm_arith_type(type_l, type_r, &v_l, &v_r);
        if (type_l == built_in_type::INT_TYPE) {
            return ir_builder.CreateICmpEQ(v_l, v_r, "eq_tmp");
        } else {
            return ir_builder.CreateFCmpOEQ(v_l, v_r, "eq_tmp");
        }
    } else {
        // TODO this part only supports char, bool and enum
        return ir_builder.CreateICmpEQ(value_l, value_r, "eq_tmp");
    }
}

llvm::Value *gen::gen_cmp_ne(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    return gen_logic_not(gen_cmp_eq(type_l, type_r, value_l, value_r));
}

llvm::Value *gen::gen_cmp_lt(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    if (type_l == built_in_type::INT_TYPE || type_l == built_in_type::REAL_TYPE) {
        llvm::Value *v_l = value_l;
        llvm::Value *v_r = value_r;
        to_llvm_arith_type(type_l, type_r, &v_l, &v_r);
        if (type_l == built_in_type::INT_TYPE) {
            return ir_builder.CreateICmpSLT(v_l, v_r, "lt_tmp");
        } else {
            return ir_builder.CreateFCmpOLT(v_l, v_r, "lt_tmp");
        }
    } else {
        return ir_builder.CreateICmpSLT(value_l, value_r, "lt_tmp");
    }
}

llvm::Value *gen::gen_cmp_gt(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    return gen_cmp_lt(type_r, type_l, value_r, value_l);
}

llvm::Value *gen::gen_cmp_le(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    return gen_logic_or(gen_cmp_lt(type_l, type_r, value_l, value_r), gen_cmp_eq(type_l, type_r, value_l, value_r));
}

llvm::Value *gen::gen_cmp_ge(
        const sem_type &type_l, const sem_type &type_r, llvm::Value *value_l, llvm::Value *value_r
) {
    return gen_logic_or(gen_cmp_gt(type_l, type_r, value_l, value_r), gen_cmp_eq(type_l, type_r, value_l, value_r));
}
