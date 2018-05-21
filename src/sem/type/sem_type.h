#ifndef MY_PASCAL_SEM_TYPE_H
#define MY_PASCAL_SEM_TYPE_H

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

struct sem_type {
    bool known;
    meta_group mg;
    type_group tg;
    int id;
};

void define_type_id(const std::string &id, sem_type type);

extern std::map<std::string, sem_type> id_type;

#endif //MY_PASCAL_SEM_TYPE_H
