#ifndef MPC_SEM_TYPE_H
#define MPC_SEM_TYPE_H

#include <string>
#include <vector>
#include <map>

enum class type_group {
    BUILT_IN, ENUM, SUBRANGE, ARRAY
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
    bool is_type = false;
    type_group tg = type_group::BUILT_IN;
    int id = built_in_type::VOID;
    int ptr = 0;

    bool operator==(const sem_type &rhs) const;

    bool operator!=(const sem_type &rhs) const;
};

namespace built_in_type {
    const sem_type VOID_TYPE = {true, type_group::BUILT_IN, VOID};
    const sem_type INT_TYPE = {true, type_group::BUILT_IN, INT};
    const sem_type REAL_TYPE = {true, type_group::BUILT_IN, REAL};
    const sem_type CHAR_TYPE = {true, type_group::BUILT_IN, CHAR};
    const sem_type BOOL_TYPE = {true, type_group::BUILT_IN, BOOL};
    const sem_type STR_TYPE = {true, type_group::BUILT_IN, STR};

    const sem_type INT_VAL = {false, type_group::BUILT_IN, INT};
    const sem_type REAL_VAL = {false, type_group::BUILT_IN, REAL};
    const sem_type CHAR_VAL = {false, type_group::BUILT_IN, CHAR};
    const sem_type BOOL_VAL = {false, type_group::BUILT_IN, BOOL};
    const sem_type STR_VAL = {false, type_group::BUILT_IN, STR};
}

class sem_type_context {
public:
    void push();

    void pop();

    const sem_type &get_type(const std::string &id) const;

    bool is_valname_used(const std::string &id) const;

    void set_type(const std::string &id, const sem_type &type);

private:
    std::vector<std::map<std::string, sem_type>> layers;
};

namespace sem {
    void set_id_type(const std::string &id, const sem_type &type);

    void define_type(const std::string &id, const sem_type &type);

    void assert_is_type(const sem_type &type);
}

#endif //MPC_SEM_TYPE_H
