#include <stdexcept>

#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/func/sys/gen_sys_write.h"

bool has_printf = false;

void register_printf() {
    std::vector<llvm::Type *> printf_arg_types;
    printf_arg_types.push_back(llvm::Type::getInt8PtrTy(llvm_context));

    llvm::FunctionType *printf_type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(llvm_context), printf_arg_types, true
    );

    llvm::Function *func = llvm::Function::Create(
            printf_type, llvm::Function::ExternalLinkage, "printf", &llvm_module
    );
    func->setCallingConv(llvm::CallingConv::C);
}

void gen::gen_write(std::vector<ast_value_node *> args, bool new_line) {
    if (!has_printf) {
        register_printf();
        has_printf = true;
    }

    std::string format;
    std::vector<llvm::Value *> printf_args;
    for (auto arg : args) {
        const sem_type &t = arg->get_type();
        if (t == built_in_type::INT_TYPE) {
            format += "%d";
        } else if (t == built_in_type::REAL_TYPE) {
            format += "%lf";
        } else if (t == built_in_type::CHAR_TYPE) {
            format += "%c";
        } else {
            throw std::invalid_argument("[gen::gen_write] Unsupported type");
        }
        printf_args.emplace_back(arg->get_llvm_value());
    }
    if (new_line) {
        format += "\n";
    }
    printf_args.insert(printf_args.begin(), ir_builder.CreateGlobalStringPtr(format, "printf_format"));

    llvm::Function *printf_func = llvm_module.getFunction("printf");
    ir_builder.CreateCall(printf_func, printf_args);
}
