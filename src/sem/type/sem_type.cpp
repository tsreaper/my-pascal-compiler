#include <cstdio>

#include "sem/exception/sem_exception.h"
#include "sem/type/sem_type.h"

std::map<std::string, sem_type> id_type;

void define_type_id(const std::string &id, sem_type type) {
    if (id_type.find(id) != id_type.end()) {
        throw sem_exception("semantics error, duplicated identifier " + id);
    } else if (!type.known) {
        throw sem_exception("semantics error, rhs is an unknown identifier");
    } else if (type.mg != meta_group::TYPE) {
        throw sem_exception("semantics error, rhs is not a type");
    }
    id_type[id] = type;
}
