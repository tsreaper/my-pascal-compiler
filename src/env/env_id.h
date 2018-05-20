#ifndef MY_PASCAL_ENV_ID_H
#define MY_PASCAL_ENV_ID_H

#include <string>

#include "env/env_type.h"
#include "env/env_value.h"

env_type get_id_type(const std::string &id);

env_value get_id_value(const std::string &id);

bool define_const_id(const std::string &id, env_type type, env_value value);

#endif //MY_PASCAL_ENV_ID_H
