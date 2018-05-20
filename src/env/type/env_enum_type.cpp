#include <cstdio>

#include "env/value/env_const.h"
#include "env/type/env_type.h"
#include "env/type/env_enum_type.h"

std::vector<env_enum_type> enum_table;

int define_enum_type(const std::vector<ast_id *> &id_vec) {
    auto enum_id = (int) enum_table.size();
    enum_table.emplace_back(env_enum_type());

    int count = 0;
    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        if (!define_const_id(
                (*it)->get_id(), {true, meta_group::CONST, type_group::ENUM, enum_id}, {true, {.num = count++}}
        )) {
            return -1;
        }
        enum_table[enum_id].id_vec.emplace_back((*it)->get_id());
    }

    return enum_id;
}
