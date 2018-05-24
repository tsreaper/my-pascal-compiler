#include <sem/value/sem_value.h>
#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/exp/ast_arith.h"

ast_arith::ast_arith(
        ast_type_node *child_l, ast_type_node *child_r
) : child_l(child_l), child_r(child_r), type({false}) {}

ast_arith::~ast_arith() {
    delete child_l;
    delete child_r;
}

const sem_type &ast_arith::get_type() const {
    return type;
}

bool ast_arith::analyse(){
    if (child_l->analyse() && child_r->analyse()) {
        try {
            type = assert_can_do_arith(child_l->get_type(), child_r->get_type());
            return true;
        } catch (const sem_exception &e) {
            PRINT_ERROR_MSG(e);
            return false;
        }
    } else {
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

ast_arith_add::ast_arith_add(ast_type_node *child_l, ast_type_node *child_r) : ast_arith(child_l, child_r) {}

void ast_arith_add::explain_impl(std::string &res, int indent) const {
    arith_explain_impl("add", res, indent);
}

ast_arith_sub::ast_arith_sub(ast_type_node *child_l, ast_type_node *child_r) : ast_arith(child_l, child_r) {}

void ast_arith_sub::explain_impl(std::string &res, int indent) const {
    arith_explain_impl("subtract", res, indent);
}

ast_arith_mul::ast_arith_mul(ast_type_node *child_l, ast_type_node *child_r) : ast_arith(child_l, child_r) {}

void ast_arith_mul::explain_impl(std::string &res, int indent) const {
    arith_explain_impl("multiply", res, indent);
}

ast_arith_div::ast_arith_div(ast_type_node *child_l, ast_type_node *child_r) : ast_arith(child_l, child_r) {}

bool ast_arith_div::analyse() {
    if (!ast_arith::analyse()) {
        return false;
    }
    type = built_in_type::REAL_TYPE;
    return true;
}

void ast_arith_div::explain_impl(std::string &res, int indent) const {
    arith_explain_impl("division", res, indent);
}

ast_arith_int_only::ast_arith_int_only(
        ast_type_node *child_l, ast_type_node *child_r
) : ast_arith(child_l, child_r) {}

bool ast_arith_int_only::analyse() {
    if (!ast_arith::analyse()) {
        return false;
    }
    try {
        if (child_l->get_type() != built_in_type::INT_TYPE || child_r->get_type() != built_in_type::INT_TYPE) {
            throw sem_exception("semantics error, must be integer type values");
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

ast_arith_div_floor::ast_arith_div_floor(
        ast_type_node *child_l, ast_type_node *child_r
) : ast_arith_int_only(child_l, child_r) {}

void ast_arith_div_floor::explain_impl(std::string &res, int indent) const {
    arith_explain_impl("division_floor", res, indent);
}

ast_arith_mod::ast_arith_mod(
        ast_type_node *child_l, ast_type_node *child_r
) : ast_arith_int_only(child_l, child_r) {}

void ast_arith_mod::explain_impl(std::string &res, int indent) const {
    arith_explain_impl("mod", res, indent);
}
