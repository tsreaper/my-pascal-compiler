#ifndef MPC_SEM_LABEL_H
#define MPC_SEM_LABEL_H

#include <vector>
#include <set>

class sem_label_context {
public:
    void push();

    void pop();

    void declare_label(int label);

    void assert_label_declared(int label);

    void use_label(int label);

    void need_label(int label);

private:
    std::vector<std::set<int>> declare_vec;
    std::vector<std::set<int>> use_vec;
    std::vector<std::set<int>> need_vec;
};

namespace sem {
    void declare_label(int label);

    void use_label(int label);

    void need_label(int label);
}

#endif //MPC_SEM_LABEL_H
