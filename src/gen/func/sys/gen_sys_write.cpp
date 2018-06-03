#include <stdexcept>

#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/func/sys/gen_sys_write.h"

static llvm::Function *printf_func = nullptr;

llvm::Function *register_printf() {
    std::vector<llvm::Type *> printf_arg_types = {llvm::Type::getInt8PtrTy(llvm_context)};

    llvm::FunctionType *printf_type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(llvm_context), printf_arg_types, true
    );

    llvm::Function *func = llvm::Function::Create(
            printf_type, llvm::Function::ExternalLinkage, "printf", &llvm_module
    );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
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
        } else if (t == built_in_type::REAL_TYPE) {
            format += "%lf";
        } else if (t == built_in_type::CHAR_TYPE) {
            format += "%c";
        } else {
            throw std::invalid_argument("[gen::gen_sys_write] Unsupported type");
        }
        printf_args.emplace_back(arg->get_llvm_value());
    }
    if (new_line) {
        format += "\n";
    }
    printf_args.insert(printf_args.begin(), ir_builder.CreateGlobalStringPtr(format, "printf_format"));

    return ir_builder.CreateCall(printf_func, printf_args);
}
