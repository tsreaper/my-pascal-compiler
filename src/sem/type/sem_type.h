#ifndef MY_PASCAL_SEM_TYPE_H
#define MY_PASCAL_SEM_TYPE_H

#include <string>
#include <vector>
#include <map>

enum class meta_group {
    CONST, VAR, TYPE
};

enum class type_group {
    BUILT_IN, ENUM, SUBRANGE
};

namespace built_in_type {
    const int VOID = -1;
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

class sem_type_context {
public:
    void push();

    void pop();

    const sem_type &get_type(const std::string &id) const;

    bool is_varname_used(const std::string &id) const;

    void set_type(const std::string &id, const sem_type &type);

private:
    std::vector<std::map<std::string, sem_type>> layers;
};

void define_type_id(const std::string &id, const sem_type &type);

#endif //MY_PASCAL_SEM_TYPE_H
