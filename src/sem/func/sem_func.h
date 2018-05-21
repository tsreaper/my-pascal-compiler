#ifndef MY_PASCAL_SEM_FUNC_H
#define MY_PASCAL_SEM_FUNC_H

#include <string>
#include <vector>

#include "ast/ast_node.h"
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

private:
    typedef std::pair<func_sign, sem_type> func_sign_ret;

    std::vector<std::vector<func_sign_ret>> layers;

    int find_signature(const func_sign &sign, const std::vector<func_sign_ret> &layer) const;
};

void declare_func(const std::string &id, const std::vector<ast_type_node*> &param_type_vec, const sem_type &ret_type);

#endif //MY_PASCAL_SEM_FUNC_H
