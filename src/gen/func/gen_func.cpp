#include <stdexcept>

#include "sem/func/sem_func.h"
#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/func/gen_func.h"

void gen_func_context::push() {
    layers.emplace_back();
}

void gen_func_context::pop() {
    layers.pop_back();
}

#define FIND_SIGNATURE(sign, layer, res) { \
    for (int i = 0; i < (layer).size(); i++) { \
        if ((sign) == (layer)[i].first) { \
            (res) = i; \
            break; \
        } \
    } \
}

bool gen_func_context::is_func_declared(const func_sign &sign) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        int pos = -1;
        FIND_SIGNATURE(sign, *it, pos);
        if (pos >= 0) {
            return true;
        }
    }
    return false;
}

llvm::Function *gen_func_context::get_func(const func_sign &sign) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        int pos = -1;
        FIND_SIGNATURE(sign, *it, pos);
        if (pos >= 0) {
            return (*it)[pos].second;
        }
    }
    throw std::invalid_argument("[gen_func_context::get_func] Unknown procedure/function " + sign.id);
}

void gen_func_context::set_func(const func_sign &sign, llvm::Function *func) {
    (*layers.rbegin()).emplace_back(func_sign_func(sign, func));
}

void gen::declare_func(const func_sign &sign, const sem_type &ret_type) {
    std::vector<llvm::Type *> args_type;
    for (auto &t : sign.param_type_vec) {
        args_type.emplace_back(get_llvm_type(t));
    }
    llvm::FunctionType *func_type = llvm::FunctionType::get(get_llvm_type(ret_type), args_type, false);
    llvm::Function *func = llvm::Function::Create(func_type, llvm::Function::ExternalLinkage, sign.id, &llvm_module);
    gen_env.get_func_env().set_func(sign, func);
}

void gen::define_func(const func_sign &sign, const sem_type &ret_type) {
    if (!gen_env.get_func_env().is_func_declared(sign)) {
        declare_func(sign, ret_type);
    }
    llvm::Function *func = get_func(sign);
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(llvm_context, "entry", func);
    ir_builder.SetInsertPoint(bb);
}

llvm::Function *gen::get_func(const func_sign &sign) {
    return gen_env.get_func_env().get_func(sign);
}
