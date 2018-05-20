#ifndef MY_PASCAL_ENV_H
#define MY_PASCAL_ENV_H

#include <string>
#include <map>

#include "env/env_type.h"
#include "env/env_value.h"

extern std::map<int, int> label_table;

extern std::map<std::string, env_type> id_type;
extern std::map<std::string, env_value> const_table;

#endif //MY_PASCAL_ENV_H
