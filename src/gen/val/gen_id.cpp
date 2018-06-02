#include <stdexcept>

#include "sem/val/sem_id.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/val/gen_literal.h"
#include "gen/val/gen_id.h"

void gen_id_context::push() {
    layers.emplace_back();
}

void gen_id_context::pop() {
    layers.pop_back();
}

llvm::Value *gen_id_context::get_mem(const std::string &id) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        if ((*it).find(id) != (*it).end()) {
            return (*it).at(id);
        }
    }
    throw std::invalid_argument("[gen_id_context::get_llvm_mem] Unknown identifier");
}

void gen_id_context::set_mem(const std::string &id, llvm::Value *mem) {
    (*layers.rbegin())[id] = mem;
}

void gen::declare_id(const std::string &id, const sem_type &type) {
    llvm::Value *mem = nullptr;
    llvm::Type *llvm_type = get_llvm_type(type);
    if (gen_env.is_global()) {
        mem = new llvm::GlobalVariable(
                llvm_module, llvm_type, false, llvm::GlobalValue::InternalLinkage,
                llvm::ConstantAggregateZero::get(llvm_type), id
        );
    } else {
        mem = ir_builder.CreateAlloca(llvm_type, nullptr, id);
    }
    gen_env.get_id_env().set_mem(id, mem);
}

llvm::Value *gen::get_mem(const std::string &id) {
    return gen_env.get_id_env().get_mem(id);
}
