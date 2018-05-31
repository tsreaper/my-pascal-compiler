#ifndef MPC_GEN_LABEL_H
#define MPC_GEN_LABEL_H

#include <vector>
#include <map>

#include <llvm/IR/BasicBlock.h>

class gen_label_context {
public:
    void push();

    void pop();

    llvm::BasicBlock *get_block(int label) const;

    void set_block(int label, llvm::BasicBlock *block);

private:
    std::vector<std::map<int, llvm::BasicBlock *>> layers;
};

namespace gen {
    llvm::BasicBlock *get_block(int label);

    void set_block(int label, llvm::BasicBlock *block);
}

#endif //MPC_GEN_LABEL_H
