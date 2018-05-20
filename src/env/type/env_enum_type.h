#ifndef MY_PASCAL_ENV_ENUM_TYPE_H
#define MY_PASCAL_ENV_ENUM_TYPE_H

#include <string>
#include <vector>

#include "ast/id/ast_id.h"

struct env_enum_type {
    int size;
    std::vector<std::string> id_vec;
};

int define_enum_type(const std::vector<ast_id*> &id_vec);

extern std::vector<env_enum_type> enum_table;

#endif //MY_PASCAL_ENV_ENUM_TYPE_H
