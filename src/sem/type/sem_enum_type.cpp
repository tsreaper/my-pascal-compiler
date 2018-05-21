#include <cstdio>

#include "sem/sem.h"
#include "sem/value/sem_const.h"
#include "sem/type/sem_type.h"
#include "sem/value/sem_value.h"
#include "sem/type/sem_enum_type.h"

void sem_enum_context::push() {
    enum_count.emplace_back();
    if (enum_count.size() > 1) {
        *enum_count.rbegin() = *prev(enum_count.rbegin());
    }
}

void sem_enum_context::pop() {
    enum_count.pop_back();
    if (!enum_count.empty()) {
        enum_table.resize((unsigned long) *enum_count.rbegin());
    } else {
        enum_table.clear();
    }
}

int sem_enum_context::add_enum_type(const std::vector<ast_id *> &id_vec) {
    auto enum_id = (int) enum_table.size();
    enum_table.emplace_back();
    *enum_count.rbegin() += 1;
    auto &current = *enum_table.rbegin();

    int count = 0;
    for (auto child : id_vec) {
        sem_type type = {true, meta_group::CONST, type_group::ENUM, enum_id};
        sem_value value = {true, {.num = count++}};
        define_const_id(child->get_id(), type, value);
        current.id_vec.emplace_back(child->get_id());
    }
    current.size = count;

    return enum_id;
}

int define_enum_type(const std::vector<ast_id *> &id_vec) {
    return sem_env.get_enum_env().add_enum_type(id_vec);
}
