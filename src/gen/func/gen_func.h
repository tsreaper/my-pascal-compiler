#ifndef MPC_GEN_FUNC_H
#define MPC_GEN_FUNC_H

#include <llvm/IR/Type.h>
#include <llvm/IR/Function.h>

#include "sem/func/sem_func.h"

class gen_func_context {
public:
    void push();

    void pop();

    bool is_func_declared(const func_sign &sign) const;

    llvm::Function *get_func(const func_sign &sign) const;

    void set_func(const func_sign &sign, llvm::Function *func);

private:
    typedef std::pair<func_sign, llvm::Function *> func_sign_func;
    std::vector<std::vector<func_sign_func>> layers;
};

namespace gen {
    void declare_func(const func_sign &sign, const sem_type &ret_type);

    void define_func(const func_sign &sign, const sem_type &ret_type);

    llvm::Function *get_func(const func_sign &sign);
}

#endif //MPC_GEN_FUNC_H
