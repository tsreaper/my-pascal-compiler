#ifndef MPC_SEM_RECORD_TYPE_H
#define MPC_SEM_RECORD_TYPE_H

#include <string>
#include <vector>

#include "ast/id/ast_id.h"
#include "sem/type/sem_type.h"

struct sem_record_type {
    int size;
    std::vector<std::string> id_vec;
    std::vector<sem_type> type_vec;
};

class sem_record_context {
public:
    void push();

    void pop();

    const sem_record_type &get_record_type(int idx) const;

    int add_record_type(const sem_record_type &type);

private:
    std::vector<sem_record_type> record_table;
    std::vector<int> record_count;
};

namespace sem {
    sem_record_type make_record_type(const std::vector<ast_id *> &id_vec, const std::vector<sem_type> &type_vec);

    int define_record_type(const sem_record_type &type);

    const sem_record_type &get_record_type_by_idx(int idx);

    void assert_is_record_value(const sem_type &type);

    int get_bias_in_record(const sem_record_type &type, const std::string &name);
}

#endif //MPC_SEM_RECORD_TYPE_H
