#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_abs.h"

static llvm::Function *abs_int_func = nullptr, *abs_real_func = nullptr;

llvm::Function *register_abs_int() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_int_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_int_type(), arg_types, false
    );
    RETURN_C_FUNC("abs");
}

llvm::Value *gen::gen_sys_abs_int(const std::vector<ast_value_node *> &args) {
    if (abs_int_func == nullptr) {
        abs_int_func = register_abs_int();
    }

    std::vector<llvm::Value *> llvm_args = {args[0]->get_llvm_value()};
    return ir_builder.CreateCall(abs_int_func, llvm_args, "call_abs_int");
}

llvm::Function *register_abs_real() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_real_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_real_type(), arg_types, false
    );
    RETURN_C_FUNC("fabs");
}

llvm::Value *gen::gen_sys_abs_real(const std::vector<ast_value_node *> &args) {
    if (abs_real_func == nullptr) {
        abs_real_func = register_abs_real();
    }

    std::vector<llvm::Value *> llvm_args = {args[0]->get_llvm_value()};
    return ir_builder.CreateCall(abs_real_func, llvm_args, "call_abs_real");
}
