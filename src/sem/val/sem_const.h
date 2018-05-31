#ifndef MPC_SEM_CONST_H
#define MPC_SEM_CONST_H

#include <string>
#include <vector>
#include <map>

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

class sem_const_context {
public:
    void push();

    void pop();

    const sem_value &get_const(const std::string &id) const;

    void set_const(const std::string &id, const sem_value &value);

private:
    std::vector<std::map<std::string, sem_value>> layers;
};

namespace sem {
    void define_const_id(const std::string &id, const sem_type &type, const sem_value &value);
}

#endif //MPC_SEM_CONST_H
