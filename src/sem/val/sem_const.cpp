#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/val/sem_const.h"

void sem_const_context::push() {
    layers.emplace_back();
}

void sem_const_context::pop() {
    layers.pop_back();
}

const sem_value &sem_const_context::get_const(const std::string &id) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        if ((*it).find(id) != (*it).end()) {
            return (*it).at(id);
        }
    }
    throw sem_exception("semantics error, unknown const identifier " + id);
}

void sem_const_context::set_const(const std::string &id, const sem_value &value) {
    auto &table = *layers.rbegin();
    if (table.find(id) != table.end() || sem_env.get_type_env().is_valname_used(id)) {
        throw sem_exception("semantics error, duplicated const identifier " + id);
    }
    table[id] = value;
}

void sem::define_const_id(const std::string &id, const sem_type &type, const sem_value &value) {
    if (!value.known) {
        throw sem_exception("semantics error, rhs is not determined");
    }
    sem_env.get_const_env().set_const(id, value);
    sem_env.get_type_env().set_type(id, type);
}
