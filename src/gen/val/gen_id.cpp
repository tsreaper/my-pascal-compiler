#include <stdexcept>

#include "sem/val/sem_id.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/val/gen_id.h"

void gen_id_context::push() {
    layers.emplace_back();
}

void gen_id_context::pop() {
    layers.pop_back();
}

llvm::AllocaInst *gen_id_context::get_alloca(const std::string &id) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        if ((*it).find(id) != (*it).end()) {
            return (*it).at(id);
        }
    }
    throw std::invalid_argument("[gen_id_context::get_alloca] Unknown identifier");
}

void gen_id_context::set_alloca(const std::string &id, llvm::AllocaInst *alloca) {
    (*layers.rbegin())[id] = alloca;
}

void gen::declare_id(const std::string &id, const sem_type &type) {
    llvm::AllocaInst *alloca = ir_builder.CreateAlloca(get_llvm_type(type), nullptr, id);
    gen_env.get_id_env().set_alloca(id, alloca);
}

llvm::AllocaInst *gen::get_alloca(const std::string &id) {
    return gen_env.get_id_env().get_alloca(id);
}
