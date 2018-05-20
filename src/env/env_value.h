#ifndef MY_PASCAL_ENV_VALUE_H
#define MY_PASCAL_ENV_VALUE_H

struct env_value {
    bool known;
    union {
        int num;
        double real;
        char chr;
        bool boo;
        const std::string *str;
    } value;
};

#endif //MY_PASCAL_ENV_VALUE_H
