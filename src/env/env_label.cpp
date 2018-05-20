#include <cstdio>

#include "env/env.h"
#include "env/env_label.h"

bool declare_label(int label) {
    if (label_table.find(label) != label_table.end()) {
        fprintf(stderr, "semantics error, duplicated label %d ", label);
        return false;
    }
    label_table[label] = -1;
    return true;
}