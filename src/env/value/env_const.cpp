#include "env/value/env_const.h"

bool define_const_id(const std::string &id, env_type type, env_value value) {
    if (id_type.find(id) != id_type.end()) {
        fprintf(stderr, "semantics error, duplicated identifier %s ", id.c_str());
        return false;
    } else if (!type.known) {
        fprintf(stderr, "semantics error, rhs is an unknown identifier ");
        return false;
    } else if (!value.known) {
        fprintf(stderr, "semantics error, rhs is not determined ");
        return false;
    }
    id_type[id] = type;
    const_table[id] = value;
    return true;
}

