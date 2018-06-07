#include <stdexcept>

#include <llvm/IR/Type.h>

#include "gen/gen.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_func.h"
#include "gen/func/sys/gen_sys_read.h"

static llvm::Value *scanf_func = nullptr;

llvm::Value *register_scanf() {
    std::vector<llvm::Type *> arg_types = {gen::get_llvm_char_ptr_type()};
    llvm::FunctionType *func_type = llvm::FunctionType::get(
            gen::get_llvm_int_type(), arg_types, true
    );
    RETURN_C_FUNC("scanf");
}

llvm::Value *gen::gen_sys_read(const std::vector<ast_value_node *> &args, bool new_line) {
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
        } else if (t.tg == type_group::STR) {
            format += "%s";
        } else {
            throw std::invalid_argument("[gen::gen_sys_read] Unsupported type");
        }
        scanf_args.emplace_back(arg->get_llvm_mem());
    }
    if (new_line) {
        format += "%*[^\n]";
    }
    scanf_args.insert(scanf_args.begin(), ir_builder.CreateGlobalStringPtr(format, "scanf_format"));

    llvm::Value *ret = ir_builder.CreateCall(scanf_func, scanf_args, "call_scanf");
    if (new_line) {
        // Consume \n
        ir_builder.CreateCall(scanf_func, ir_builder.CreateGlobalStringPtr("%*c", "scanf_newline"), "call_scanf");
    }
    return ret;
}
