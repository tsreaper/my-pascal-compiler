#include "sem/stmt/sem_loop.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/stmt/gen_loop.h"
#include "ast/stmt/loop/ast_break.h"

bool ast_break::semantics_self() {
    try {
        sem::assert_in_loop();
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_break::codegen() {
    ir_builder.CreateBr(gen::get_current_loop()->get_break_block());
}

void ast_break::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "break()\n";
}
