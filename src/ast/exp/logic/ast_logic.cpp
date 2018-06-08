#include "sem/exp/sem_logic.h"
#include "sem/exception/sem_exception.h"
#include "gen/exp/gen_logic.h"
#include "ast/exp/logic/ast_logic.h"

ast_logic::ast_logic(ast_value_node *child_l, ast_value_node *child_r) : ast_binop(child_l, child_r) {
    s_type = built_in_type::BOOL_VAL;
}

bool ast_logic::analyse(bool as_rval) {
    MUST_BE_RVAL;

    // And/Or operators are short circuit evaluated
    if (!semantics_l()) {
        return false;
    }
    codegen_l();

    if (!s_value.known) {
        if (!semantics_r()) {
            return false;
        }
        codegen_r();
    }

    return true;
}

bool ast_logic::semantics_l() {
    if (!child_l->analyse()) {
        return false;
    }
    try {
        if (child_l->get_type() != built_in_type::BOOL_TYPE) {
            throw sem_exception("semantics error, left operand must be a boolean value");
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

bool ast_logic::semantics_r() {
    if (!child_r->analyse()) {
        return false;
    }
    try {
        if (child_r->get_type() != built_in_type::BOOL_TYPE) {
            throw sem_exception("semantics error, right operand must be a boolean value");
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}
