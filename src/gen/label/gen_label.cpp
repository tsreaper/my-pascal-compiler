#include "gen/gen.h"
#include "gen/label/gen_label.h"

void gen_label_context::push() {
    layers.emplace_back();
}

void gen_label_context::pop() {
    layers.pop_back();
}

llvm::BasicBlock *gen_label_context::get_block(int label) const {
    auto &table = *layers.rbegin();
    auto it = table.find(label);
    if (it == table.end()) {
        return nullptr;
    } else {
        return it->second;
    }
}

void gen_label_context::set_block(int label, llvm::BasicBlock *block) {
    (*layers.rbegin())[label] = block;
}

llvm::BasicBlock *gen::get_block(int label) {
    return gen_env.get_label_env().get_block(label);
}

void gen::set_block(int label, llvm::BasicBlock *block) {
    gen_env.get_label_env().set_block(label, block);
}
