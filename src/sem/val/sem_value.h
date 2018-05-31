#ifndef MPC_SEM_VALUE_H
#define MPC_SEM_VALUE_H

#include <string>
#include <map>

struct sem_value {
    bool known;
    union {
        int num;
        double real;
        char chr;
        bool boo;
        const std::string *str;
    } value;
};

namespace built_in_value {
    const sem_value UNKNOWN_VALUE = {false};
}

#endif //MPC_SEM_VALUE_H
