#include "env/value/env_var.h"

bool declare_var_id(const std::string &id, env_type type) {
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
    id_type[id] = {true, meta_group::VAR, type.tg, type.id};
    return true;
}
