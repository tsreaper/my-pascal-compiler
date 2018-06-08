#include "sem/exp/sem_binop.h"
#include "sem/exception/sem_exception.h"
#include "ast/exp/ast_binop.h"

ast_binop::ast_binop(ast_value_node *child_l, ast_value_node *child_r) : child_l(child_l), child_r(child_r) {}

ast_binop::~ast_binop() {
    delete child_l;
    delete child_r;
}

bool ast_binop::semantics_child() {
    return child_l->analyse() && child_r->analyse();
}

bool ast_binop::semantics_self() {
    try {
        sem::binop_type_compare(child_l->get_type(), child_r->get_type(), conv_type_l, conv_type_r);
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }

    return semantics_op();
}

bool ast_binop::semantics_op() {
    return true;
}

void ast_binop::binop_explain_impl(const std::string &op_name, std::string &res, int indent) const {
    explain_indent(res, indent);
    res += op_name + "(\n";
    child_l->explain_impl(res, indent + 1);
    child_r->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
