#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem_id.h"

const sem_type &sem::get_id_type(const std::string &id) {
    return sem_env.get_type_env().get_type(id);
}

const sem_value &sem::get_id_value(const std::string &id) {
    try {
        return sem_env.get_const_env().get_const(id);
    } catch (const sem_exception &e) {
        return built_in_value::UNKNOWN_VALUE;
    }
}

bool sem::is_const_id(const std::string &id) {
    try {
        sem_env.get_const_env().get_const(id);
        return true;
    } catch (const sem_exception &e) {
        return false;
    }
}

bool sem::is_used_id(const std::string &id) {
    return sem_env.get_type_env().is_valname_used(id);
}
