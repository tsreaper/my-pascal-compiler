#include "sem/exception/sem_exception.h"
#include "ast/exp/ast_logic.h"

ast_logic::ast_logic(ast_type_node *child_l, ast_type_node *child_r) : child_l(child_l), child_r(child_r) {
    type = built_in_type::EXP_BOOL_TYPE;
}

ast_logic::~ast_logic() {
    delete child_l;
    delete child_r;
}

const sem_type &ast_logic::get_type() const {
    return type;
}

bool ast_logic::semantics_child() {
    return (code_l = child_l->analyse()) != nullptr && (code_r = child_r->analyse()) != nullptr;
}

bool ast_logic::semantics_self() {
    try {
        type = assert_can_do_logic(child_l->get_type(), child_r->get_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_logic::logic_explain_impl(const std::string &op_name, std::string &res, int indent) const {
    explain_indent(res, indent);
    res += op_name + "(\n";
    child_l->explain_impl(res, indent + 1);
    child_r->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}

ast_logic_and::ast_logic_and(ast_type_node *child_l, ast_type_node *child_r) : ast_logic(child_l, child_r) {}

void ast_logic_and::explain_impl(std::string &res, int indent) const {
    logic_explain_impl("and", res, indent);
}

ast_logic_or::ast_logic_or(ast_type_node *child_l, ast_type_node *child_r) : ast_logic(child_l, child_r) {}

void ast_logic_or::explain_impl(std::string &res, int indent) const {
    logic_explain_impl("or", res, indent);
}

ast_logic_xor::ast_logic_xor(ast_type_node *child_l, ast_type_node *child_r) : ast_logic(child_l, child_r) {}

void ast_logic_xor::explain_impl(std::string &res, int indent) const {
    logic_explain_impl("xor", res, indent);
}

ast_logic_not::ast_logic_not(ast_type_node *child) : child(child) {
    type = built_in_type::EXP_BOOL_TYPE;
}

ast_logic_not::~ast_logic_not() {
    delete child;
}

const sem_type &ast_logic_not::get_type() const {
    return type;
}

bool ast_logic_not::semantics_child() {
    return (code_ch = child->analyse()) != nullptr;
}

bool ast_logic_not::semantics_self() {
    try {
        const sem_type &t = child->get_type();
        if (t.mg != meta_group::TYPE && t == built_in_type::BOOL_TYPE) {
            return true;
        }
        throw sem_exception("semantics error, must be a boolean type value");
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_logic_not::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "not(\n";
    child->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
