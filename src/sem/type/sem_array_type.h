#ifndef MPC_SEM_ARRAY_TYPE_H
#define MPC_SEM_ARRAY_TYPE_H

#include <vector>

#include "ast/exp/ast_exp_seq.h"
#include "ast/type/ast_range_type.h"
#include "sem/type/sem_type.h"

struct sem_array_type {
    sem_type ele_type;
    int size;
    std::vector<int> range_vec;

    bool operator==(const sem_array_type &rhs) const;
};

namespace sem {
    sem_array_type make_array_type(const std::vector<ast_range_type *> &range_vec, ast_type_node *ele_type);

    sem_array_type make_array_type_from_exp_seq(ast_exp_seq *seq);

    int get_or_define_array_type(const sem_array_type &type);

    const sem_array_type &get_array_type_by_idx(int idx);

    void assert_is_array_value(const sem_type &type);

    bool array_can_assign(const sem_type &type_l, const sem_type &type_r);
}

#endif //MPC_SEM_ARRAY_TYPE_H
