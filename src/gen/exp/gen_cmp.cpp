#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/exp/gen_logic.h"
#include "gen/exp/gen_cmp.h"

llvm::Value *gen::gen_cmp_eq(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    if (type == built_in_type::REAL_TYPE) {
        return ir_builder.CreateFCmpOEQ(value_l, value_r, "eq_tmp");
    } else {
        return ir_builder.CreateICmpEQ(value_l, value_r, "eq_tmp");
    }
}

llvm::Value *gen::gen_cmp_ne(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    return gen_logic_not(gen_cmp_eq(type, value_l, value_r));
}

llvm::Value *gen::gen_cmp_lt(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    if (type == built_in_type::REAL_TYPE) {
        return ir_builder.CreateFCmpOLT(value_l, value_r, "lt_tmp");
    } else {
        return ir_builder.CreateICmpSLT(value_l, value_r, "lt_tmp");
    }
}

llvm::Value *gen::gen_cmp_gt(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    return gen_cmp_lt(type, value_r, value_l);
}

llvm::Value *gen::gen_cmp_le(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    return gen_logic_or(gen_cmp_lt(type, value_l, value_r), gen_cmp_eq(type, value_l, value_r));
}

llvm::Value *gen::gen_cmp_ge(const sem_type &type, llvm::Value *value_l, llvm::Value *value_r) {
    return gen_logic_or(gen_cmp_gt(type, value_l, value_r), gen_cmp_eq(type, value_l, value_r));
}
