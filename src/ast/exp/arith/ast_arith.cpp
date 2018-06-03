#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"
#include "sem/exp/sem_arith.h"
#include "sem/exception/sem_exception.h"
#include "ast/exp/arith/ast_arith.h"

ast_arith::ast_arith(ast_value_node *child_l, ast_value_node *child_r) : child_l(child_l), child_r(child_r) {}

ast_arith::~ast_arith() {
    delete child_l;
    delete child_r;
}

bool ast_arith::analyse(bool as_rval) {
    MUST_BE_RVAL;

    if (semantics_child() && semantics_self()) {
        if (child_l->get_value().known && child_r->get_value().known) {
            try {
                do_arith();
            } catch (const sem_exception &e) {
                PRINT_ERROR_MSG(e);
                return false;
            }
        }
        codegen();
        return true;
    } else {
        return false;
    }
}

bool ast_arith::semantics_child() {
    return child_l->analyse() && child_r->analyse();
}

bool ast_arith::semantics_self() {
    try {
        s_type = sem::assert_can_do_arith(child_l->get_type(), child_r->get_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_arith::arith_explain_impl(const std::string &op_name, std::string &res, int indent) const {
    explain_indent(res, indent);
    res += op_name + "(\n";
    child_l->explain_impl(res, indent + 1);
    child_r->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}

ast_int_arith::ast_int_arith(ast_value_node *child_l, ast_value_node *child_r) : ast_arith(child_l, child_r) {}

bool ast_int_arith::semantics_self() {
    if (!ast_arith::semantics_self()) {
        return false;
    }
    try {
        if (child_l->get_type() != built_in_type::INT_TYPE || child_r->get_type() != built_in_type::INT_TYPE) {
            throw sem_exception("semantics error, must be integer type values");
        }
        if (child_r->get_value().known && child_r->get_value().value.num == 0) {
            throw sem_exception("semantics error, cannot divide zero");
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}
