#ifndef MY_PASCAL_SEM_LABEL_H
#define MY_PASCAL_SEM_LABEL_H

#include <map>

void declare_label(int label);

extern std::map<int, int> label_table;

#endif //MY_PASCAL_SEM_LABEL_H
