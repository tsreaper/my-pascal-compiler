#ifndef MPC_SEM_EXCEPTION_H
#define MPC_SEM_EXCEPTION_H

#include <string>

class sem_exception : public std::exception {
public:
    explicit sem_exception(const std::string &msg);

    const char *what() const noexcept override;

private:
    std::string msg;
};

#endif //MPC_SEM_EXCEPTION_H
