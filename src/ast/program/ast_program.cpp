#include "sem/sem.h"
#include "sem/func/sem_func.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "gen/program/gen_program.h"
#include "gen/func/gen_exit.h"
#include "ast/program/ast_program.h"

ast_program_head::ast_program_head(const std::string &name) : name(name) {}

void ast_program_head::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "program_head(" + name + ")\n";
}

ast_program::ast_program(ast_program_head *head, ast_block *block) : head(head), block(block) {}

ast_program::~ast_program() {
    delete head;
    delete block;
}

#define ENV_POP { \
    try { \
        gen_env.pop(); \
        sem_env.pop(); \
    } catch (const sem_exception &e) { \
        PRINT_ERROR_MSG(e); \
        return false; \
    } \
}

bool ast_program::analyse() {
    sem_env.push();
    gen_env.push(func_sign{"main"});

    codegen_phase1();

    if (!semantics_child()) {
        ENV_POP;
        return false;
    }

    codegen_phase2();
    ENV_POP;
    return true;
}

bool ast_program::semantics_child() {
    return head->analyse() && block->analyse();
}

void ast_program::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "program(\n";

    head->explain_impl(res, indent + 1);
    block->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

void ast_program::codegen_phase1() {
    gen::define_main();
}

void ast_program::codegen_phase2() {
    gen::gen_exit();
}
