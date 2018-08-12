#include <cstring>
#include <iostream>
#include <string>

#include "make/compile.h"
#include "make/outfile.h"

static bool debug = false;
static std::string input_file;
static std::string output_file;
static outfile_type file_type = outfile_type::OUT;

void print_usage() {
    printf(
            "NAME\n"
            "        mpc - My Pascal compiler\n"
            "\n"
            "USAGE\n"
            "        mpc [-d] [-t filetype] [-o outfile] infile\n"
            "\n"
            "OPTIONS\n"
            "        -d\n"
            "            Prints debug message.\n"
            "\n"
            "        -t filetype\n"
            "            Specify what kind of output mpc should generate. `filetype` can be\n"
            "                ll: llvm IR code\n"
            "                asm: textual assembly\n"
            "                obj: native object file\n"
            "\n"
            "        -o outfile\n"
            "            Rename output file of mpc to `outfile`\n"
    );
}

bool parse_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            debug = true;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 >= argc) {
                return false;
            } else {
                output_file = argv[i + 1];
                i++;
            }
        } else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 >= argc) {
                return false;
            } else if (strcmp(argv[i + 1], "ll") == 0) {
                file_type = outfile_type::LL;
                i++;
            } else if (strcmp(argv[i + 1], "asm") == 0) {
                file_type = outfile_type::ASM;
                i++;
            } else if (strcmp(argv[i + 1], "obj") == 0) {
                file_type = outfile_type::OBJ;
                i++;
            } else {
                return false;
            }
        } else {
            if (input_file.empty()) {
                input_file = argv[i];
            } else {
                return false;
            }
        }
    }

    if (input_file.empty()) {
        return false;
    }

    if (output_file.empty()) {
        switch (file_type) {
            case outfile_type::OUT:
                output_file = "a.out";
                break;
            case outfile_type::LL:
                output_file = input_file + ".ll";
                break;
            case outfile_type::ASM:
                output_file = input_file + ".s";
                break;
            case outfile_type::OBJ:
                output_file = input_file + ".o";
                break;
            default:
                return false;
        }
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (!parse_args(argc, argv)) {
        print_usage();
        return 1;
    }

    if (!make::compile(input_file, debug)) {
        return 2;
    }

    if (!make::gen_outfile(output_file, file_type, debug)) {
        return 3;
    }

    return 0;
}
