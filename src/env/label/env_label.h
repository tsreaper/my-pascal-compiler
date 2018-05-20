#ifndef MY_PASCAL_ENV_LABEL_H
#define MY_PASCAL_ENV_LABEL_H

#include <map>

bool declare_label(int label);

extern std::map<int, int> label_table;

#endif //MY_PASCAL_ENV_LABEL_H
