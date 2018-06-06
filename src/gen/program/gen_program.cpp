#include "gen/gen.h"
#include "gen/type/gen_builtin_type.h"
#include "gen/program/gen_program.h"

void gen::define_main() {
    llvm::FunctionType *func_type = llvm::FunctionType::get(get_llvm_int_type(), false);
    llvm::Function *main_func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, "main", &llvm_module);
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(llvm_context, "entry", main_func);
    ir_builder.SetInsertPoint(entry);
}
