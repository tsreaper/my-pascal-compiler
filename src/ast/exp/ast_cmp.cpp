#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/exp/ast_cmp.h"

ast_cmp::ast_cmp(ast_type_node *child_l, ast_type_node *child_r) : child_l(child_l), child_r(child_r) {
    type = built_in_type::EXP_BOOL_TYPE;
}

ast_cmp::~ast_cmp() {
    delete child_l;
    delete child_r;
}

const sem_type &ast_cmp::get_type() const {
    return type;
}

bool ast_cmp::semantics_child() {
    return (code_l = child_l->analyse()) != nullptr && (code_r = child_r->analyse()) != nullptr;
}

bool ast_cmp::cmp_semantics_impl(bool need_eq, bool need_cmp) {
    try {
        if (need_eq) {
            type = assert_can_equal(child_l->get_type(), child_r->get_type());
        }
        if (need_cmp) {
            type = assert_can_compare(child_l->get_type(), child_r->get_type());
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_cmp::cmp_explain_impl(const std::string &op_name, std::string &res, int indent) const {
    explain_indent(res, indent);
    res += op_name + "(\n";
    child_l->explain_impl(res, indent + 1);
    child_r->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}

ast_cmp_eq::ast_cmp_eq(ast_type_node *child_l, ast_type_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_eq::semantics_self() {
    return cmp_semantics_impl(true, false);
}

void ast_cmp_eq::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("equal", res, indent);
}

ast_cmp_ne::ast_cmp_ne(ast_type_node *child_l, ast_type_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_ne::semantics_self() {
    return cmp_semantics_impl(true, false);
}

void ast_cmp_ne::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("not_equal", res, indent);
}

ast_cmp_lt::ast_cmp_lt(ast_type_node *child_l, ast_type_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_lt::semantics_self() {
    return cmp_semantics_impl(false, true);
}

void ast_cmp_lt::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("less_than", res, indent);
}

ast_cmp_gt::ast_cmp_gt(ast_type_node *child_l, ast_type_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_gt::semantics_self() {
    return cmp_semantics_impl(false, true);
}

void ast_cmp_gt::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("greater_than", res, indent);
}

ast_cmp_le::ast_cmp_le(ast_type_node *child_l, ast_type_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_le::semantics_self() {
    return cmp_semantics_impl(true, true);
}

void ast_cmp_le::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("less_than_or_equal", res, indent);
}

ast_cmp_ge::ast_cmp_ge(ast_type_node *child_l, ast_type_node *child_r) : ast_cmp(child_l, child_r) {}

bool ast_cmp_ge::semantics_self() {
    return cmp_semantics_impl(true, true);
}

void ast_cmp_ge::explain_impl(std::string &res, int indent) const {
    cmp_explain_impl("greater_than_or_equal", res, indent);
}
