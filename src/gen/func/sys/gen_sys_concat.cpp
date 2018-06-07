#include <llvm/IR/Type.h>

#include "sem/type/sem_str_type.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_concat.h"

static llvm::Function *strcat_func = nullptr;

llvm::Function *register_strcat() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_char_ptr_type(), gen::get_llvm_char_ptr_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_char_ptr_type(), arg_types, false
    );
    RETURN_C_FUNC("strcat");
}

llvm::Value *gen::gen_sys_concat(const std::vector<ast_value_node *> &args) {
    std::vector<llvm::Value *> mem_vec;
    int dest_len = 0;
    for (auto &child : args) {
        mem_vec.emplace_back(child->get_llvm_mem());
        dest_len += child->get_type().id;
    }
    return gen_sys_concat_impl(mem_vec, dest_len);
}

llvm::Value *gen::gen_sys_concat_impl(const std::vector<llvm::Value *> &mem_vec, int dest_len) {
    if (strcat_func == nullptr) {
        strcat_func = register_strcat();
    }

    llvm::Value *dest = ir_builder.CreateAlloca(
            get_llvm_str_type(sem::get_str_type_by_len(dest_len)), nullptr, "concat_dest"
    );
    llvm::Value *dest_begin = ir_builder.CreateGEP(dest, {get_llvm_int(0), get_llvm_int(0)}, "concat_dest_addr");
    // Initialize dest to empty string
    ir_builder.CreateStore(get_llvm_char(0), dest_begin);

    for (auto &mem : mem_vec) {
        ir_builder.CreateCall(
                strcat_func,
                {dest_begin, ir_builder.CreateGEP(mem, {get_llvm_int(0), get_llvm_int(0)}, "concat_src_addr")},
                "call_strcat"
        );
    }
    return ir_builder.CreateLoad(dest, "concat_res");
}
