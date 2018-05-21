#include "sem/exception/sem_exception.h"
#include "sem/value/sem_const.h"

void define_const_id(const std::string &id, sem_type type, sem_value value) {
    if (id_type.find(id) != id_type.end()) {
        throw sem_exception("semantics error, duplicated identifier " + id);
    } else if (!type.known) {
        throw sem_exception("semantics error, rhs is an unknown identifier " + id);
    } else if (!value.known) {
        throw sem_exception("semantics error, rhs is not determined " + id);
    }
    id_type[id] = type;
    const_table[id] = value;
}
