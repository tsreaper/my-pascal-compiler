#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_type.h"

bool sem_type::operator==(const sem_type &rhs) const {
    if (!known || !rhs.known) {
        return false;
    }
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

const sem_type &assert_can_do_arith(const sem_type &type_l, const sem_type &type_r) {
    if (type_l.mg != meta_group::TYPE && type_r.mg != meta_group::TYPE) {
        if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::INT_TYPE) {
            return built_in_type::EXP_INT_TYPE;
        } else if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::REAL_TYPE) {
            return built_in_type::EXP_REAL_TYPE;
        } else if (type_l == built_in_type::REAL_TYPE && type_r == built_in_type::INT_TYPE) {
            return built_in_type::EXP_REAL_TYPE;
        }
    }

    throw sem_exception("semantics error, must be integer type values or real type values");
}

const sem_type &assert_can_do_logic(const sem_type &type_l, const sem_type &type_r) {
    if (type_l.mg != meta_group::TYPE && type_r.mg != meta_group::TYPE) {
        if (type_l == built_in_type::BOOL_TYPE && type_r == built_in_type::BOOL_TYPE) {
            return built_in_type::EXP_BOOL_TYPE;
        }
    }

    throw sem_exception("semantics error, must be boolean type values");
}

const sem_type &assert_can_equal(const sem_type &type_l, const sem_type &type_r) {
    if (type_l.mg != meta_group::TYPE && type_r.mg != meta_group::TYPE) {
        if (
                (type_l == built_in_type::INT_TYPE || type_l == built_in_type::REAL_TYPE) &&
                (type_r == built_in_type::INT_TYPE || type_r == built_in_type::REAL_TYPE)
        ) {
            return built_in_type::EXP_BOOL_TYPE;
        }
        if (type_l != built_in_type::VOID_TYPE && type_l == type_r) {
            return built_in_type::EXP_BOOL_TYPE;
        }
    }

    throw sem_exception(
            "semantics error, cannot check the equality of these two values because their types are inconsistent"
    );
}

const sem_type &assert_can_compare(const sem_type &type_l, const sem_type &type_r) {
    if (
            type_l.mg != meta_group::TYPE && type_r.mg != meta_group::TYPE &&
            type_l.tg == type_group::BUILT_IN && type_r.tg == type_group::BUILT_IN
    ) {
        if (
                (type_l == built_in_type::INT_TYPE || type_l == built_in_type::REAL_TYPE) &&
                (type_r == built_in_type::INT_TYPE || type_r == built_in_type::REAL_TYPE)
                ) {
            return built_in_type::EXP_BOOL_TYPE;
        }
        if (type_l != built_in_type::VOID_TYPE && type_l == type_r) {
            return built_in_type::EXP_BOOL_TYPE;
        }
    }

    throw sem_exception("semantics error, cannot compare these two values because their types are inconsistent");
}

void assert_can_assign(const sem_type &type_l, const sem_type &type_r) {
    if (type_l.mg != meta_group::VAR) {
        throw sem_exception("semantics error, only variables can be assigned");
    }
    if (type_r.mg != meta_group::TYPE) {
        if (type_l == type_r) {
            return;
        } else if (type_l == built_in_type::REAL_TYPE && type_r == built_in_type::INT_TYPE) {
            return;
        }
    }
    throw sem_exception("semantics error, cannot assign rhs to variable because their types are inconsistent");
}
