#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_type.h"

bool sem_type::operator==(const sem_type &rhs) const {
    return tg == rhs.tg && id == rhs.id;
}

bool sem_type::operator!=(const sem_type &rhs) const {
    return !(*this == rhs);
}

void sem_type_context::push() {
    layers.emplace_back();
}

void sem_type_context::pop() {
    layers.pop_back();
}

const sem_type &sem_type_context::get_type(const std::string &id) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        if ((*it).find(id) != (*it).end()) {
            return (*it).at(id);
        }
    }
    throw sem_exception("semantics error, unknown identifier " + id);
}

bool sem_type_context::is_varname_used(const std::string &id) const {
    auto &table = *layers.rbegin();
    return table.find(id) != table.end();
}

void sem_type_context::set_type(const std::string &id, const sem_type &type) {
    auto &table = *layers.rbegin();
    if (table.find(id) != table.end()) {
        throw sem_exception("semantics error, duplicated identifier " + id);
    }
    table[id] = type;
}

void define_type_id(const std::string &id, const sem_type &type) {
    if (!type.known) {
        throw sem_exception("semantics error, rhs is an unknown type");
    } else if (type.mg != meta_group::TYPE) {
        throw sem_exception("semantics error, rhs is not a type");
    }
    sem_env.get_type_env().set_type(id, type);
}

void assert_is_type(const sem_type &type) {
    if (type.mg != meta_group::TYPE) {
        throw sem_exception("semantics error, not a type");
    }
}
