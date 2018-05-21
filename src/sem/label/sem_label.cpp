#include <map>

#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/label/sem_label.h"

void sem_label_context::push() {
    layers.emplace_back();
}

void sem_label_context::pop() {
    layers.pop_back();
}

int sem_label_context::get_loc(int label) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        if ((*it).find(label) != (*it).end()) {
            return (*it).at(label);
        }
    }
    throw sem_exception("semantics error, undeclared label " + std::to_string(label));
}

void sem_label_context::set_loc(int label, int loc) {
    auto &table = *layers.rbegin();
    if (loc == -1 && table.find(label) != table.end()) {
        throw sem_exception("semantics error, duplicated label " + std::to_string(label));
    }
    table[label] = loc;
}

void declare_label(int label) {
    sem_env.get_label_env().set_loc(label, -1);
}
