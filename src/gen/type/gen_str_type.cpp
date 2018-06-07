#include "sem/type/sem_str_type.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_logic.h"
#include "gen/func/sys/gen_sys_concat.h"
#include "gen/func/sys/gen_sys_strcmp.h"
#include "gen/type/gen_builtin_type.h"
#include "gen/type/gen_str_type.h"

llvm::ArrayType *gen::get_llvm_str_type(const sem_type &type) {
    return llvm::ArrayType::get(get_llvm_char_type(), (uint64_t) type.id + 1);
}

llvm::Value *gen::gen_char_to_str_mem(llvm::Value *c) {
    llvm::Value *mem = ir_builder.CreateAlloca(get_llvm_str_type(sem::get_str_type_by_len(1)), nullptr, "c2s");

    ir_builder.CreateStore(c, ir_builder.CreateGEP(mem, {get_llvm_int(0), get_llvm_int(0)}, "c2s_first_char"));
    ir_builder.CreateStore(
            get_llvm_char(0), ir_builder.CreateGEP(mem, {get_llvm_int(0), get_llvm_int(1)}, "c2s_last_char")
    );
    return mem;
}

llvm::Value *gen::gen_str_add(int dest_len, llvm::Value *value_l, llvm::Value *value_r) {
    llvm::Value *mem_l = ((llvm::LoadInst *) value_l)->getPointerOperand();
    llvm::Value *mem_r = ((llvm::LoadInst *) value_r)->getPointerOperand();
    return gen_sys_concat_impl({mem_l, mem_r}, dest_len);
}

llvm::Value *gen::gen_str_eq(llvm::Value *value_l, llvm::Value *value_r) {
    llvm::Value *mem_l = ((llvm::LoadInst *) value_l)->getPointerOperand();
    llvm::Value *mem_r = ((llvm::LoadInst *) value_r)->getPointerOperand();
    return ir_builder.CreateICmpEQ(gen_sys_strcmp_impl(mem_l, mem_r), get_llvm_int(0), "str_eq_tmp");
}

llvm::Value *gen::gen_str_ne(llvm::Value *value_l, llvm::Value *value_r) {
    return gen_logic_not(gen_str_eq(value_l, value_r));
}

llvm::Value *gen::gen_str_lt(llvm::Value *value_l, llvm::Value *value_r) {
    llvm::Value *mem_l = ((llvm::LoadInst *) value_l)->getPointerOperand();
    llvm::Value *mem_r = ((llvm::LoadInst *) value_r)->getPointerOperand();
    return ir_builder.CreateICmpSLT(gen_sys_strcmp_impl(mem_l, mem_r), get_llvm_int(0), "str_lt_tmp");
}

llvm::Value *gen::gen_str_gt(llvm::Value *value_l, llvm::Value *value_r) {
    return gen_str_lt(value_r, value_l);
}

llvm::Value *gen::gen_str_le(llvm::Value *value_l, llvm::Value *value_r) {
    return gen_logic_or(gen_str_lt(value_l, value_r), gen_str_eq(value_l, value_r));
}

llvm::Value *gen::gen_str_ge(llvm::Value *value_l, llvm::Value *value_r) {
    return gen_logic_or(gen_str_gt(value_l, value_r), gen_str_eq(value_l, value_r));
}
