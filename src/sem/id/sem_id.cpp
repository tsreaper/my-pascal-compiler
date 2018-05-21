#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/id/sem_id.h"

const sem_type &get_id_type(const std::string &id) {
    return sem_env.get_type_env().get_type(id);
}

const sem_value &get_id_value(const std::string &id) {
    return sem_env.get_const_env().get_const(id);
}
