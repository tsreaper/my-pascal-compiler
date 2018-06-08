#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_fillchar.h"

static llvm::Value *memset_func = nullptr;

llvm::Value *register_memset() {
    std::vector<llvm::Type *> arg_types = {
            gen::get_llvm_char_ptr_type(),
            gen::get_llvm_int_type(),
            gen::get_llvm_int_type()
    };
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_char_ptr_type(), arg_types, false
    );
    RETURN_C_FUNC("memset");
}

llvm::Value *gen::gen_sys_fillchar(const std::vector<ast_value_node *> &args) {
    if (memset_func == nullptr) {
        memset_func = register_memset();
    }
    return ir_builder.CreateCall(
            memset_func, {
                ir_builder.CreateBitCast(args[0]->get_llvm_mem(), get_llvm_char_ptr_type()),
                ir_builder.CreateIntCast(args[2]->get_llvm_value(), get_llvm_int_type(), true),
                args[1]->get_llvm_value()
            }, "call_memset"
    );
}
