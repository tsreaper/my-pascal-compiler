#include "sem/exception/sem_exception.h"

sem_exception::sem_exception(const std::string &msg) : msg(msg) {}

const char *sem_exception::what() const noexcept {
    return msg.c_str();
}
