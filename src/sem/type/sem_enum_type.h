#ifndef MY_PASCAL_SEM_ENUM_TYPE_H
#define MY_PASCAL_SEM_ENUM_TYPE_H

#include <string>
#include <vector>

#include "ast/id/ast_id.h"

struct sem_enum_type {
    int size;
    std::vector<std::string> id_vec;
};

int define_enum_type(const std::vector<ast_id*> &id_vec);

extern std::vector<sem_enum_type> enum_table;

#endif //MY_PASCAL_SEM_ENUM_TYPE_H
