#ifndef MPC_GEN_ID_H
#define MPC_GEN_ID_H

#include <string>
#include <vector>
#include <map>

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"

class gen_id_context {
public:
    void push();

    void pop();

    llvm::Value *get_mem(const std::string &id) const;

    void set_mem(const std::string &id, llvm::Value *alloca);

private:
    std::vector<std::map<std::string, llvm::Value *>> layers;
};

namespace gen {
    void declare_id(const std::string &id, const sem_type &type);

    llvm::Value *get_mem(const std::string &id);
}

#endif //MPC_GEN_ID_H
