#include <cstdio>

#include "sem/id/sem_id.h"

sem_type get_id_type(const std::string &id) {
    if (id_type.find(id) == id_type.end()) {
        return {false};
    } else {
        return id_type.at(id);
    }
}

sem_value get_id_value(const std::string &id) {
    if (const_table.find(id) == const_table.end()) {
        return {false};
    } else {
        return const_table.at(id);
    }
}
