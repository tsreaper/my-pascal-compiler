#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "pascal.y.hpp"

#include "ast/ast.h"
#include "make/compile.h"

void explain_ast() {
    std::string plan;
    ast_root->explain(plan);
    std::cerr << plan << std::endl;
}

bool make::compile(const std::string &filename, bool debug) {
    int fd = open(filename.c_str(), O_RDONLY);
    if (fd < 0) {
        std::cerr << "cannot open file " << filename << ", errno: " << errno << std::endl;
        return false;
    }
    if (dup2(fd, 0) < 0) {
        std::cerr << "cannot dup input file to stdin, errno: " << errno << std::endl;
        return false;
    }
    close(fd);

    struct stat file_stat;
    stat(filename.c_str(), &file_stat);
    if (!S_ISREG(file_stat.st_mode)) {
        std::cerr << filename << " is not a regular file" << std::endl;
        return false;
    }

    if (yyparse() != 0) {
        return false;
    }
    if (debug) {
        explain_ast();
    }

    return ast_root->analyse();
}
