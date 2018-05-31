#ifndef MPC_GEN_H
#define MPC_GEN_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

#include "gen/val/gen_id.h"
#include "gen/func/gen_func.h"
#include "gen/stmt/gen_loop.h"

class gen_context {
public:
    void push();

    void pop();

    bool is_global();

    gen_id_context &get_id_env();

    gen_func_context &get_func_env();

    gen_loop_context &get_loop_env();

private:
    int depth = 0;

    gen_id_context id_env;
    gen_func_context func_env;
    gen_loop_context loop_env;
};

extern llvm::LLVMContext llvm_context;
extern llvm::Module llvm_module;
extern llvm::IRBuilder<> ir_builder;

extern gen_context gen_env;

#endif //MPC_GEN_H
