#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/exp/gen_cmp.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_min.h"

static llvm::Function *min_int_func = nullptr;

llvm::Function *register_min_int() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_int_type(), gen::get_llvm_int_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_int_type(), arg_types, false
    );
    llvm::Function *func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "min", &llvm_module);
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(llvm_context, "entry", func);
    llvm::BasicBlock *old_bb = ir_builder.GetInsertBlock();
    ir_builder.SetInsertPoint(bb);

    llvm::BasicBlock *a_bb = llvm::BasicBlock::Create(llvm_context, "min_a", func);
    llvm::BasicBlock *b_bb = llvm::BasicBlock::Create(llvm_context, "min_b", func);
    auto arg_it = func->arg_begin();
    ir_builder.CreateCondBr(gen::gen_cmp_lt(built_in_type::INT_TYPE, arg_it, arg_it + 1), a_bb, b_bb);
    ir_builder.SetInsertPoint(a_bb);

    ir_builder.CreateRet(arg_it);
    ir_builder.SetInsertPoint(b_bb);

    ir_builder.CreateRet(arg_it + 1);
    ir_builder.SetInsertPoint(old_bb);

    return func;
}

llvm::Value *gen::gen_sys_min_int_impl(llvm::Value *a, llvm::Value *b) {
    if (min_int_func == nullptr) {
        min_int_func = register_min_int();
    }
    return ir_builder.CreateCall(min_int_func, {a, b}, "call_min_int");
}
