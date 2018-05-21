#ifndef MY_PASCAL_SEM_EXCEPTION_H
#define MY_PASCAL_SEM_EXCEPTION_H

#include <string>

struct sem_exception : public std::exception {
    std::string msg;

    explicit sem_exception(const std::string &msg);
};

#endif //MY_PASCAL_SEM_EXCEPTION_H
