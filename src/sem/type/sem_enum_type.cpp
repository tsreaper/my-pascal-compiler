#include <cstdio>

#include "sem/value/sem_const.h"
#include "sem/type/sem_type.h"
#include "sem/type/sem_enum_type.h"

std::vector<sem_enum_type> enum_table;

int define_enum_type(const std::vector<ast_id *> &id_vec) {
    auto enum_id = (int) enum_table.size();
    enum_table.emplace_back(sem_enum_type());

    int count = 0;
    for (auto child : id_vec) {
        define_const_id(
                child->get_id(), {true, meta_group::CONST, type_group::ENUM, enum_id}, {true, {.num = count++}}
        );
        enum_table[enum_id].id_vec.emplace_back(child->get_id());
    }

    return enum_id;
}
