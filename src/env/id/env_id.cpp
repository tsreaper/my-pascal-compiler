#include <cstdio>

#include "env/id/env_id.h"

env_type get_id_type(const std::string &id) {
    if (id_type.find(id) == id_type.end()) {
        return {false};
    } else {
        return id_type.at(id);
    }
}

env_value get_id_value(const std::string &id) {
    if (const_table.find(id) == const_table.end()) {
        return {false};
    } else {
        return const_table.at(id);
    }
}
