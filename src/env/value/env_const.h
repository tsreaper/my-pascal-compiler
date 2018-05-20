#ifndef MY_PASCAL_ENV_CONST_H
#define MY_PASCAL_ENV_CONST_H

#include <string>

#include "env/type/env_type.h"
#include "env/value/env_value.h"

bool define_const_id(const std::string &id, env_type type, env_value value);

#endif //MY_PASCAL_ENV_CONST_H
