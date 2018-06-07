#include <stdexcept>

#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_write.h"

static llvm::Function *printf_func = nullptr;

llvm::Function *register_printf() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_char_ptr_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_int_type(), arg_types, true
    );
    RETURN_C_FUNC("printf");
}

llvm::Value *gen::gen_sys_write(const std::vector<ast_value_node *> &args, bool new_line) {
    if (printf_func == nullptr) {
        printf_func = register_printf();
    }

    std::string format;
    std::vector<llvm::Value *> printf_args;
    for (auto &arg : args) {
        const sem_type &t = arg->get_type();
        if (t == built_in_type::INT_TYPE) {
            format += "%d";
            printf_args.emplace_back(arg->get_llvm_value());
        } else if (t == built_in_type::REAL_TYPE) {
            format += "%lf";
            printf_args.emplace_back(arg->get_llvm_value());
        } else if (t == built_in_type::CHAR_TYPE) {
            format += "%c";
            printf_args.emplace_back(arg->get_llvm_value());
        } else if (t.tg == type_group::STR) {
            format += "%s";
            printf_args.emplace_back(arg->get_llvm_mem());
        } else {
            throw std::invalid_argument("[gen::gen_sys_write] Unsupported type");
        }
    }
    if (new_line) {
        format += "\n";
    }
    printf_args.insert(printf_args.begin(), ir_builder.CreateGlobalStringPtr(format, "printf_format"));

    return ir_builder.CreateCall(printf_func, printf_args, "call_printf");
}
