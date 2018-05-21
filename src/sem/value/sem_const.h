#ifndef MY_PASCAL_SEM_CONST_H
#define MY_PASCAL_SEM_CONST_H

#include <string>
#include <vector>
#include <map>

#include "sem/type/sem_type.h"
#include "sem/value/sem_value.h"

class sem_const_context {
public:
    void push();

    void pop();

    const sem_value &get_const(const std::string &id) const;

    void set_const(const std::string &id, const sem_value &value);

private:
    std::vector<std::map<std::string, sem_value>> layers;
};

void define_const_id(const std::string &id, const sem_type &type, const sem_value &value);

#endif //MY_PASCAL_SEM_CONST_H
