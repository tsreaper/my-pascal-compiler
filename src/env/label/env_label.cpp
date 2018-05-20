#include <cstdio>
#include <map>

#include "env/label/env_label.h"

std::map<int, int> label_table;

bool declare_label(int label) {
    if (label_table.find(label) != label_table.end()) {
        fprintf(stderr, "semantics error, duplicated label %d ", label);
        return false;
    }
    label_table[label] = -1;
    return true;
}
