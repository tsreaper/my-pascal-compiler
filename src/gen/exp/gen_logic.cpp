#include "gen/gen.h"
#include "gen/exp/gen_logic.h"

llvm::Value *gen::gen_logic_and(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateAnd(value_l, value_r);
}

llvm::Value *gen::gen_logic_or(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateOr(value_l, value_r);
}

llvm::Value *gen::gen_logic_xor(llvm::Value *value_l, llvm::Value *value_r) {
    return ir_builder.CreateXor(value_l, value_r);
}

llvm::Value *gen::gen_logic_not(llvm::Value *value) {
    return ir_builder.CreateNot(value);
}
