#include "sem/stmt/sem_assign.h"
#include "sem/exception/sem_exception.h"
#include "ast/exp/ptr/ast_at.h"

ast_at::ast_at(ast_value_node *lval) : lval(lval) {}

ast_at::~ast_at() {
    delete lval;
}

bool ast_at::semantics_child() {
    return lval->analyse(false);
}

bool ast_at::semantics_self() {
    try {
        sem::assert_is_variable(lval);
        s_type = lval->get_type();
        s_type.ptr++;
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_at::codegen() {
    llvm_value = lval->get_llvm_mem();
}

void ast_at::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "at(\n";
    lval->explain_impl(res, indent + 1);
    res += ")\n";
}
