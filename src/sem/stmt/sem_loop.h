#ifndef MPC_SEM_LOOP_H
#define MPC_SEM_LOOP_H

#include <vector>
#include <string>

class sem_loop_context {
public:
    void push();

    void pop();

    bool empty() const;

private:
    int depth = 0;
};

namespace sem {
    void assert_in_loop();
}

#endif //MPC_SEM_LOOP_H
