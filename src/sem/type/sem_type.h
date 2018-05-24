#ifndef MY_PASCAL_SEM_TYPE_H
#define MY_PASCAL_SEM_TYPE_H

#include <string>
#include <vector>
#include <map>

enum class meta_group {
    CONST, VAR, TYPE, EXP
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

    bool operator==(const sem_type &rhs) const;

    bool operator!=(const sem_type &rhs) const;
};

namespace built_in_type {
    const sem_type VOID_TYPE = {true, meta_group::TYPE, type_group::BUILT_IN, VOID};
    const sem_type INT_TYPE = {true, meta_group::TYPE, type_group::BUILT_IN, INT};
    const sem_type REAL_TYPE = {true, meta_group::TYPE, type_group::BUILT_IN, REAL};
    const sem_type CHAR_TYPE = {true, meta_group::TYPE, type_group::BUILT_IN, CHAR};
    const sem_type BOOL_TYPE = {true, meta_group::TYPE, type_group::BUILT_IN, BOOL};
    const sem_type STR_TYPE = {true, meta_group::TYPE, type_group::BUILT_IN, STR};

    const sem_type CONST_INT_TYPE = {true, meta_group::CONST, type_group::BUILT_IN, INT};
    const sem_type CONST_REAL_TYPE = {true, meta_group::CONST, type_group::BUILT_IN, REAL};
    const sem_type CONST_CHAR_TYPE = {true, meta_group::CONST, type_group::BUILT_IN, CHAR};
    const sem_type CONST_BOOL_TYPE = {true, meta_group::CONST, type_group::BUILT_IN, BOOL};
    const sem_type CONST_STR_TYPE = {true, meta_group::CONST, type_group::BUILT_IN, STR};

    const sem_type EXP_INT_TYPE = {true, meta_group::EXP, type_group::BUILT_IN, INT};
    const sem_type EXP_REAL_TYPE = {true, meta_group::EXP, type_group::BUILT_IN, REAL};
    const sem_type EXP_BOOL_TYPE = {true, meta_group::EXP, type_group::BUILT_IN, BOOL};
}

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

void assert_is_type(const sem_type &type);

const sem_type &assert_can_do_arith(const sem_type &type_l, const sem_type &type_r);

const sem_type &assert_can_do_logic(const sem_type &type_l, const sem_type &type_r);

const sem_type &assert_can_equal(const sem_type &type_l, const sem_type &type_r);

const sem_type &assert_can_compare(const sem_type &type_l, const sem_type &type_r);

void assert_can_assign(const sem_type &type_l, const sem_type &type_r);

#endif //MY_PASCAL_SEM_TYPE_H
