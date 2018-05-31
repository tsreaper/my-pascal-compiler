#ifndef MPC_SEM_FUNC_H
#define MPC_SEM_FUNC_H

#include <string>
#include <vector>

#include "sem/type/sem_type.h"

struct func_sign {
    std::string id;
    std::vector<sem_type> param_type_vec;

    bool operator==(const func_sign &rhs) const;

    bool operator!=(const func_sign &rhs) const;
};

class sem_func_context {
public:
    void push();

    void pop();

    const sem_type &get_ret_type(const func_sign &sign) const;

    void set_ret_type(const func_sign &sign, const sem_type &ret_type);

    void set_defined(const func_sign &sign);

private:
    typedef std::pair<func_sign, sem_type> func_sign_ret;
    std::vector<std::vector<func_sign_ret>> type_layers;

    typedef std::pair<func_sign, bool> func_sign_defined;
    std::vector<std::vector<func_sign_defined>> defined_layers;
};

namespace sem {
    void declare_func(const func_sign &sign, const sem_type &ret_type);

    void define_func(const func_sign &sign, const sem_type &ret_type);

    const sem_type &get_ret_type(const func_sign &sign);
}

#endif //MPC_SEM_FUNC_H
