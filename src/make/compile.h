#ifndef MPC_COMPILE_H
#define MPC_COMPILE_H

#include <string>

namespace make {
    bool compile(const std::string &filename, bool debug = false);
}

#endif //MPC_COMPILE_H
