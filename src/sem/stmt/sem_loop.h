#ifndef MPC_SEM_LOOP_H
#define MPC_SEM_LOOP_H

#include <vector>
#include <string>

class sem_loop_context {
public:
    void push(const std::string &id = "");

    void pop();

    bool empty() const;

    bool is_loop_var(const std::string &id) const;

private:
    std::vector<std::string> id_vec;
};

namespace sem {
    void assert_not_loop_var(const std::string &id);

    void assert_in_loop();
}

#endif //MPC_SEM_LOOP_H
