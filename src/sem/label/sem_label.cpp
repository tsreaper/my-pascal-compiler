#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/label/sem_label.h"

void sem_label_context::push() {
    declare_vec.emplace_back();
    use_vec.emplace_back();
    need_vec.emplace_back();
}

#define POP { \
    declare_vec.pop_back(); \
    use_vec.pop_back(); \
    need_vec.pop_back(); \
};

void sem_label_context::pop() {
    for (auto label : *need_vec.rbegin()) {
        auto &table = *use_vec.rbegin();
        if (table.find(label) == table.end()) {
            POP;
            throw sem_exception("semantics error, label " + std::to_string(label) + " is not defined");
        }
    }
    POP;
}

void sem_label_context::declare_label(int label) {
    auto &table = *declare_vec.rbegin();
    if (table.find(label) != table.end()) {
        throw sem_exception("semantics error, duplicated label " + std::to_string(label));
    }
    table.insert(label);
}

void sem_label_context::assert_label_declared(int label) {
    auto &table = *declare_vec.rbegin();
    if (table.find(label) == table.end()) {
        throw sem_exception("semantics error, undeclared label " + std::to_string(label));
    }
}

void sem_label_context::use_label(int label) {
    assert_label_declared(label);
    auto &table = *use_vec.rbegin();
    if (table.find(label) != table.end()) {
        throw sem_exception("semantics error, label " + std::to_string(label) + " is defined multiple times");
    }
    table.insert(label);
}

void sem_label_context::need_label(int label) {
    assert_label_declared(label);
    (*need_vec.rbegin()).insert(label);
}

void sem::declare_label(int label) {
    sem_env.get_label_env().declare_label(label);
}

void sem::use_label(int label) {
    sem_env.get_label_env().use_label(label);
}

void sem::need_label(int label) {
    sem_env.get_label_env().need_label(label);
}
