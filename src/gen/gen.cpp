#include <vector>
#include <llvm/IR/Type.h>

#include "gen/gen.h"

llvm::LLVMContext llvm_context;
llvm::Module llvm_module("my_pascal_module", llvm_context);
llvm::IRBuilder<> ir_builder(llvm_context);

gen_context gen_env;

void gen_context::push() {
    label_env.push();
    id_env.push();
    func_env.push();
}

void gen_context::pop() {
    label_env.pop();
    id_env.pop();
    func_env.pop();
}

gen_label_context &gen_context::get_label_env() {
    return label_env;
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
