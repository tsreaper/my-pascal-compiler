#include "sem/exception/sem_exception.h"
#include "sem/value/sem_var.h"

void declare_var_id(const std::string &id, sem_type type) {
    if (id_type.find(id) != id_type.end()) {
        throw sem_exception("semantics error, duplicated identifier " + id);
    } else if (!type.known) {
        throw sem_exception("semantics error, rhs is an unknown identifier");
    } else if (type.mg != meta_group::TYPE) {
        throw sem_exception("semantics error, rhs is not a type");
    }
    id_type[id] = {true, meta_group::VAR, type.tg, type.id};
}
