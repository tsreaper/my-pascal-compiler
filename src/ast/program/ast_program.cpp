#include "sem/sem.h"
#include "gen/gen.h"
#include "gen/program/gen_program.h"
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

bool ast_program::analyse() {
    sem_env.push();
    gen_env.push();
    pre_codegen();
    bool res = semantics_child();
    gen_env.pop();
    sem_env.pop();
    return res;
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

void ast_program::pre_codegen() {
    gen::gen_main();
}
