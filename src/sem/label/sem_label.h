#ifndef MY_PASCAL_SEM_LABEL_H
#define MY_PASCAL_SEM_LABEL_H

#include <vector>
#include <map>

class sem_label_context {
public:
    void push();

    void pop();

    int get_loc(int label) const;

    void set_loc(int label, int loc);

private:
    std::vector<std::map<int, int>> layers;
};

void declare_label(int label);

#endif //MY_PASCAL_SEM_LABEL_H
