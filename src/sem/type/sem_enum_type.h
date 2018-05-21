#ifndef MY_PASCAL_SEM_ENUM_TYPE_H
#define MY_PASCAL_SEM_ENUM_TYPE_H

#include <string>
#include <vector>

#include "ast/id/ast_id.h"

struct sem_enum_type {
    int size;
    std::vector<std::string> id_vec;
};

class sem_enum_context {
public:
    void push();

    void pop();

    int add_enum_type(const std::vector<ast_id*> &id_vec);

private:
    std::vector<sem_enum_type> enum_table;
    std::vector<int> enum_count;
};

int define_enum_type(const std::vector<ast_id *> &id_vec);

#endif //MY_PASCAL_SEM_ENUM_TYPE_H
