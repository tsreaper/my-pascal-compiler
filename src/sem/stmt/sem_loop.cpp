#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/stmt/sem_loop.h"

void sem_loop_context::push(const std::string &id) {
    id_vec.emplace_back(id);
}

void sem_loop_context::pop() {
    id_vec.pop_back();
}

bool sem_loop_context::empty() const {
    return id_vec.empty();
}

bool sem_loop_context::is_loop_var(const std::string &id) const {
    for (auto const &s : id_vec) {
        if (s == id) {
            return true;
        }
    }
    return false;
}

void sem::assert_not_loop_var(const std::string &id) {
    if (sem_env.get_loop_env().is_loop_var(id)) {
        throw sem_exception("semantics error, " + id + " is a loop variable and cannot be assigned");
    }
}

void sem::assert_in_loop() {
    if (sem_env.get_loop_env().empty()) {
        throw sem_exception("semantics error, must be contained in a loop");
    }
}
