#include <map>

#include "sem/exception/sem_exception.h"
#include "sem/label/sem_label.h"

std::map<int, int> label_table;

void declare_label(int label) {
    if (label_table.find(label) != label_table.end()) {
        throw sem_exception("semantics error, duplicated label " + std::to_string(label));
    }
    label_table[label] = -1;
}
