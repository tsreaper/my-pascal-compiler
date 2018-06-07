#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_all_types.h"
#include "gen/val/gen_literal.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_strcmp.h"

static llvm::Function *strcmp_func = nullptr;

llvm::Function *register_strcmp() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_char_ptr_type(), gen::get_llvm_char_ptr_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_int_type(), arg_types, false
    );
    RETURN_C_FUNC("strcmp");
}

llvm::Value *gen::gen_sys_strcmp_impl(llvm::Value *mem_l, llvm::Value *mem_r) {
    if (strcmp_func == nullptr) {
        strcmp_func = register_strcmp();
    }
    return ir_builder.CreateCall(
            strcmp_func, {
                    ir_builder.CreateGEP(mem_l, {get_llvm_int(0), get_llvm_int(0)}, "strcmp_l_addr"),
                    ir_builder.CreateGEP(mem_r, {get_llvm_int(0), get_llvm_int(0)}, "strcmp_r_addr")
            },
            "call_strcmp"
    );
}
