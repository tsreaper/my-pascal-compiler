#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <llvm/Support/Error.h>

#include "gen/gen.h"
#include "make/outfile.h"

bool gen_out(const std::string &in, const std::string &out) {
    std::string tmp_file = in + ".s";

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "fail to fork another process, errno: " << errno << std::endl;
        return false;
    } else if (pid == 0) {
        execlp("llc", "llc", "-relocation-model=pic", in.c_str(), "-o", tmp_file.c_str(), NULL);
        std::cerr << "fail to execute llc, errno: " << errno << std::endl;
        exit(1);
    } else {
        int stat;
        wait(&stat);
        if (WEXITSTATUS(stat)) {
            std::cerr << "llc child process execution failure" << std::endl;
            remove(in.c_str());
            remove(tmp_file.c_str());
            return false;
        }
    }

    pid = fork();
    if (pid < 0) {
        std::cerr << "fail to fork another process, errno: " << errno << std::endl;
        return false;
    } else if (pid == 0) {
        execlp("gcc", "gcc", "-o", out.c_str(), tmp_file.c_str(), "-lm", NULL);
        std::cerr << "fail to execute gcc, errno: " << errno << std::endl;
        exit(1);
    } else {
        int stat;
        wait(&stat);
        if (WEXITSTATUS(stat)) {
            std::cerr << "gcc child process execution failure" << std::endl;
            remove(in.c_str());
            remove(tmp_file.c_str());
            remove(out.c_str());
            return false;
        }
    }

    remove(in.c_str());
    remove(tmp_file.c_str());
    return true;
}

bool gen_ll(const std::string &in, const std::string &out) {
    if (rename(in.c_str(), out.c_str()) < 0) {
        std::cerr << "fail to rename, errno: " << errno << std::endl;
        remove(in.c_str());
        return false;
    }
    return true;
}

bool gen_asm(const std::string &in, const std::string &out) {
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "fail to fork another process, errno: " << errno << std::endl;
        return false;
    } else if (pid == 0) {
        execlp("llc", "llc", "-relocation-model=pic", "-filetype=asm", in.c_str(), "-o", out.c_str(), NULL);
        std::cerr << "fail to execute llc, errno: " << errno << std::endl;
        exit(1);
    } else {
        int stat;
        wait(&stat);
        if (WEXITSTATUS(stat)) {
            std::cerr << "llc child process execution failure" << std::endl;
            remove(in.c_str());
            return false;
        }
    }

    remove(in.c_str());
    return true;
}

bool gen_obj(const std::string &in, const std::string &out) {
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "fail to fork another process, errno: " << errno << std::endl;
        return false;
    } else if (pid == 0) {
        execlp("llc", "llc", "-relocation-model=pic", "-filetype=obj", in.c_str(), "-o", out.c_str(), NULL);
        std::cerr << "fail to execute llc, errno: " << errno << std::endl;
        exit(1);
    } else {
        int stat;
        wait(&stat);
        if (WEXITSTATUS(stat)) {
            std::cerr << "llc child process execution failure" << std::endl;
            remove(in.c_str());
            return false;
        }
    }

    remove(in.c_str());
    return true;
}

bool make::gen_outfile(const std::string &filename, outfile_type type, bool debug) {
    std::string tmp_file = "." + filename + ".ll";
    int fd = open(tmp_file.c_str(), O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        std::cerr << "cannot generate output file " << filename << ", errno: " << errno << std::endl;
        return false;
    }
    if (dup2(fd, 1) < 0) {
        std::cerr << "cannot dup output file to stdout, errno: " << errno << std::endl;
        return false;
    }
    close(fd);

    llvm_module.print(llvm::outs(), nullptr);

    switch (type) {
        case outfile_type::OUT:
            return gen_out(tmp_file, filename);
        case outfile_type::LL:
            return gen_ll(tmp_file, filename);
        case outfile_type::ASM:
            return gen_asm(tmp_file, filename);
        case outfile_type::OBJ:
            return gen_obj(tmp_file, filename);
        default:
            return false;
    }
}
