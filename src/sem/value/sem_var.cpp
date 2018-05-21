#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/value/sem_var.h"

void declare_var_id(const std::string &id, const sem_type &type) {
    if (!type.known) {
        throw sem_exception("semantics error, rhs is an unknown type");
    } else if (type.mg != meta_group::TYPE) {
        throw sem_exception("semantics error, rhs is not a type");
    }
    sem_type var_type = {true, meta_group::VAR, type.tg, type.id};
    sem_env.get_type_env().set_type(id, var_type);
}
