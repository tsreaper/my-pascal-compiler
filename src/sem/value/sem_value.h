#ifndef MY_PASCAL_SEM_VALUE_H
#define MY_PASCAL_SEM_VALUE_H

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

#endif //MY_PASCAL_SEM_VALUE_H
