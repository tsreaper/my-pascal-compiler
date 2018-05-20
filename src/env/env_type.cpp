#include <cstdio>

#include "env/env_type.h"

std::map<std::string, env_type> id_type;

bool define_type_id(const std::string &id, env_type type) {
    if (id_type.find(id) != id_type.end()) {
        fprintf(stderr, "semantics error, duplicated identifier %s ", id.c_str());
        return false;
    } else if (!type.known) {
        fprintf(stderr, "semantics error, rhs is an unknown identifier ");
        return false;
    } else if (type.mg != meta_group::TYPE) {
        fprintf(stderr, "semantics error, rhs is not a type ");
        return false;
    }
    id_type[id] = type;
    return true;
}
