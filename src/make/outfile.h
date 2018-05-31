#ifndef MPC_OUTFILE_H
#define MPC_OUTFILE_H

#include <string>

enum class outfile_type {
    OUT, LL, ASM, OBJ
};

namespace make {
    bool gen_outfile(const std::string &filename, outfile_type type, bool debug = false);
}

#endif //MPC_OUTFILE_H
