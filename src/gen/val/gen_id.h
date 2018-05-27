#ifndef MY_PASCAL_GEN_ID_H
#define MY_PASCAL_GEN_ID_H

#include <string>
#include <vector>
#include <map>

#include <llvm/IR/Instructions.h>

#include "sem/type/sem_type.h"

class gen_id_context {
public:
    void push();

    void pop();

    llvm::AllocaInst *get_alloca(const std::string &id) const;

    void set_alloca(const std::string &id, llvm::AllocaInst *alloca);

private:
    std::vector<std::map<std::string, llvm::AllocaInst *>> layers;
};

namespace gen {
    void declare_id(const std::string &id, const sem_type &type);

    llvm::AllocaInst *get_alloca(const std::string &id);
}

#endif //MY_PASCAL_GEN_ID_H
