#include "sem/exp/sem_logic.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_logic.h"
#include "sem/exception/sem_exception.h"
#include "ast/exp/logic/ast_logic_not.h"

ast_logic_not::ast_logic_not(ast_value_node *child) : child(child), s_type(built_in_type::BOOL_VAL), s_value({false}) {}

ast_logic_not::~ast_logic_not() {
    delete child;
}

const sem_type &ast_logic_not::get_type() const {
    return s_type;
}

const sem_value &ast_logic_not::get_value() const {
    return s_value;
}

bool ast_logic_not::analyse() {
    if (semantics_child() && semantics_self()) {
        if (child->get_value().known) {
            do_logic();
        }
        codegen();
        return true;
    } else {
        return false;
    }
}

bool ast_logic_not::semantics_child() {
    return child->analyse();
}

bool ast_logic_not::semantics_self() {
    try {
        const sem_type &t = child->get_type();
        if (!t.is_type && t == built_in_type::BOOL_TYPE) {
            return true;
        }
        throw sem_exception("semantics error, must be a boolean type val");
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_logic_not::codegen() {
    if (s_value.known) {
        llvm_value = gen::get_llvm_const(s_type, s_value);
    } else {
        llvm_value = gen::gen_logic_not(child->get_llvm_value());
    }
}

void ast_logic_not::do_logic() {
    s_value = sem::do_logic_not(child->get_value());
}

void ast_logic_not::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "not(\n";
    child->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
