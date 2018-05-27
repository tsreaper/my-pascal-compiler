#include "sem/exception/sem_exception.h"
#include "gen/exp/gen_logic.h"
#include "ast/exp/logic/ast_logic.h"

ast_logic::ast_logic(
        ast_value_node *child_l, ast_value_node *child_r
) : child_l(child_l), child_r(child_r), s_type(built_in_type::BOOL_VAL), s_value({false}) {}

ast_logic::~ast_logic() {
    delete child_l;
    delete child_r;
}

const sem_type &ast_logic::get_type() const {
    return s_type;
}

const sem_value &ast_logic::get_value() const {
    return s_value;
}

bool ast_logic::analyse() {
    if (semantics_child() && semantics_self()) {
        if (child_l->get_value().known && child_r->get_value().known) {
            do_logic();
        }
        codegen();
        return true;
    } else {
        return false;
    }
}

bool ast_logic::semantics_child() {
    return child_l->analyse() && child_r->analyse();
}

bool ast_logic::semantics_self() {
    try {
        sem::assert_can_do_logic(child_l->get_type(), child_r->get_type());
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
