#ifndef MY_PASCAL_ENV_TYPE_H
#define MY_PASCAL_ENV_TYPE_H

#include <string>
#include <map>

enum class meta_group {
    CONST, VAR, TYPE
};

enum class type_group {
    BUILT_IN, ENUM, SUBRANGE
};

namespace built_in_type {
    const int INT = 0;
    const int REAL = 1;
    const int CHAR = 2;
    const int BOOL = 3;
    const int STR = 4;
}

struct env_type {
    bool known;
    meta_group mg;
    type_group tg;
    int id;
};

bool define_type_id(const std::string &id, env_type type);

extern std::map<std::string, env_type> id_type;

#endif //MY_PASCAL_ENV_TYPE_H
