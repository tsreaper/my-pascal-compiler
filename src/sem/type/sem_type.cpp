#include "sem/sem.h"
#include "sem/val/sem_id.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_type.h"

bool sem_type::operator==(const sem_type &rhs) const {
    return tg == rhs.tg && id == rhs.id && ptr == rhs.ptr;
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

bool sem_type_context::is_valname_used(const std::string &id) const {
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

void sem::set_id_type(const std::string &id, const sem_type &type) {
    if (!type.is_type) {
        throw sem_exception("semantics error, rhs is not a type");
    }
    sem_env.get_type_env().set_type(id, {false, type.tg, type.id, type.ptr});
}

void sem::define_type(const std::string &id, const sem_type &type) {
    if (!type.is_type) {
        throw sem_exception("semantics error, rhs is not a type");
    }
    sem_env.get_type_env().set_type(id, type);
}

void sem::assert_is_type(const sem_type &type) {
    if (!type.is_type) {
        throw sem_exception("semantics error, not a type");
    }
}

void sem::assert_can_be_range(const sem_type &type_l, const sem_type &type_r) {
    if (type_l.is_type || type_r.is_type) {
        throw sem_exception("semantics error, must be two values");
    }
    if (type_l != type_r) {
        throw sem_exception("semantics error, two values must be of same type");
    }
    if (type_l == built_in_type::INT_TYPE) {
        return;
    }
    if (type_l == built_in_type::CHAR_TYPE) {
        return;
    }
    if (type_l.tg == type_group::ENUM) {
        return;
    }
    throw sem_exception("semantics error, must be integer, character or enum type");
}
