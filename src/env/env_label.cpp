#include <cstdio>

#include "env/env.h"
#include "env/env_label.h"

bool register_label(int label) {
    if (label_table.find(label) != label_table.end()) {
        fprintf(stderr, "semantics error, duplicated label %d\n", label);
        return false;
    }
    label_table[label] = -1;
    return true;
}