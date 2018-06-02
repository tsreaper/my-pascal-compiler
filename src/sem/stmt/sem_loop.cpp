#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/stmt/sem_loop.h"

void sem_loop_context::push() {
    depth++;
}

void sem_loop_context::pop() {
    depth--;
}

bool sem_loop_context::empty() const {
    return depth == 0;
}

void sem::assert_in_loop() {
    if (sem_env.get_loop_env().empty()) {
        throw sem_exception("semantics error, must be contained in a loop");
    }
}
