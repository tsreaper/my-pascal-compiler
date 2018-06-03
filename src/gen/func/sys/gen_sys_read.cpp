#include <stdexcept>

#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/func/sys/gen_sys_read.h"

static llvm::Value *scanf_func = nullptr;

llvm::Value *register_scanf() {
    std::vector<llvm::Type *> scanf_arg_types = {llvm::Type::getInt8PtrTy(llvm_context)};

    llvm::FunctionType *scanf_type = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(llvm_context), scanf_arg_types, true
    );

    llvm::Function *func = llvm::Function::Create(
            scanf_type, llvm::Function::ExternalLinkage, "scanf", &llvm_module
    );
    func->setCallingConv(llvm::CallingConv::C);
    return func;
}

llvm::Value *gen::gen_sys_read(const std::vector<ast_value_node *> &args) {
    if (scanf_func == nullptr) {
        scanf_func = register_scanf();
    }

    std::string format;
    std::vector<llvm::Value *> scanf_args;
    for (auto &arg : args) {
        const sem_type &t = arg->get_type();
        if (t == built_in_type::INT_TYPE) {
            format += "%d";
        } else if (t == built_in_type::REAL_TYPE) {
            format += "%lf";
        } else if (t == built_in_type::CHAR_TYPE) {
            format += "%c";
        } else {
            throw std::invalid_argument("[gen::gen_read] Unsupported type");
        }
        scanf_args.emplace_back(arg->get_llvm_mem());
    }
    scanf_args.insert(scanf_args.begin(), ir_builder.CreateGlobalStringPtr(format, "scanf_format"));

    return ir_builder.CreateCall(scanf_func, scanf_args);
}
