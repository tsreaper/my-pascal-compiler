#include "sem/exception/sem_exception.h"
#include "gen/func/gen_func.h"
#include "ast/func/ast_func_dec.h"

ast_func_dec::ast_func_dec(ast_func_head *head) : head(head) {}

ast_func_dec::~ast_func_dec() {
    delete head;
}

bool ast_func_dec::semantics_child() {
    return head->analyse();
}

bool ast_func_dec::semantics_self() {
    try {
        sem::declare_func(head->get_func_sign(), head->get_ret_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_func_dec::codegen() {
    gen::declare_func(head->get_func_sign(), head->get_ret_type());
}

void ast_func_dec::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "function_declaration(\n";
    head->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
