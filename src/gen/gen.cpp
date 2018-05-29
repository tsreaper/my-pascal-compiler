#include <vector>
#include <llvm/IR/Type.h>

#include "gen/gen.h"

llvm::LLVMContext llvm_context;
llvm::Module llvm_module("my_pascal_module", llvm_context);
llvm::IRBuilder<> ir_builder(llvm_context);

gen_context gen_env;

/*
const llvm::Function *const intri_func::get_do_nothing() {
    std::vector<llvm::Type *> no_args;
    return llvm::Intrinsic::getDeclaration(&llvm_module, llvm::Intrinsic::donothing, no_args);
}
*/

void gen_context::push() {
    depth++;
    id_env.push();
    func_env.push();
}

void gen_context::pop() {
    depth--;
    id_env.pop();
    func_env.pop();
}

bool gen_context::is_global() {
    return depth == 1;
}

gen_id_context &gen_context::get_id_env() {
    return id_env;
}

gen_func_context &gen_context::get_func_env() {
    return func_env;
}

gen_loop_context &gen_context::get_loop_env() {
    return loop_env;
}
