#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/exp/gen_arith.h"
#include "gen/val/gen_literal.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_min_max.h"
#include "gen/func/sys/gen_sys_copy.h"

static llvm::Function *strncpy_func = nullptr;

llvm::Function *register_strncpy() {
    std::vector<llvm::Type *> arg_types = {
            gen::get_llvm_char_ptr_type(),
            gen::get_llvm_char_ptr_type(),
            gen::get_llvm_int_type()
    };
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_char_ptr_type(), arg_types, false
    );
    RETURN_C_FUNC("strncpy");
}

llvm::Value *gen::gen_sys_copy(const std::vector<ast_value_node *> &args) {
    if (args[0]->get_type() == built_in_type::CHAR_TYPE) {
        return ir_builder.CreateLoad(gen_char_to_str_mem(args[0]->get_llvm_value()), "copy_res");
    } else {
        return gen_sys_copy_impl(
                args[0]->get_llvm_mem(),
                args[1]->get_llvm_value(),
                args[2]->get_llvm_value(),
                args[0]->get_type().id
        );
    }
}

llvm::Value *gen::gen_sys_copy_impl(llvm::Value *src_mem, llvm::Value *idx, llvm::Value *cnt, int dest_len) {
    if (strncpy_func == nullptr) {
        strncpy_func = register_strncpy();
    }

    // Call strncpy
    llvm::Value *dest = ir_builder.CreateAlloca(
            get_llvm_str_type({false, type_group::STR, dest_len}), nullptr, "copy_dest"
    );
    llvm::Value *copy_len = gen_sys_min_int_impl(cnt, get_llvm_int(dest_len));
    std::vector<llvm::Value *> llvm_args = {
            ir_builder.CreateGEP(
                    dest, {get_llvm_int(0), get_llvm_int(0)}, "copy_dest_gep"
            ),
            ir_builder.CreateGEP(
                    src_mem, {get_llvm_int(0), gen_arith_sub_one(built_in_type::INT_TYPE, idx)}, "copy_src_gep"
            ),
            copy_len
    };
    ir_builder.CreateCall(strncpy_func, llvm_args, "call_strncpy");

    // Set last char to 0
    ir_builder.CreateStore(
            get_llvm_char(0),
            ir_builder.CreateGEP(dest, {get_llvm_int(0), copy_len}, "copy_dest_last_char")
    );

    return ir_builder.CreateLoad(dest, "copy_res");
}
