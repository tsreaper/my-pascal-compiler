#ifndef MY_PASCAL_ENV_ID_H
#define MY_PASCAL_ENV_ID_H

#include <string>

#include "env/type/env_type.h"
#include "env/value/env_value.h"

env_type get_id_type(const std::string &id);

env_value get_id_value(const std::string &id);

#endif //MY_PASCAL_ENV_ID_H
