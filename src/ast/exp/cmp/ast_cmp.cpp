#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "gen/exp/gen_cmp.h"
#include "ast/exp/cmp/ast_cmp.h"

ast_cmp::ast_cmp(
        ast_value_node *child_l, ast_value_node *child_r
) : child_l(child_l), child_r(child_r), s_type(built_in_type::BOOL_VAL), s_value({false}) {}

ast_cmp::~ast_cmp() {
    delete child_l;
    delete child_r;
}

const sem_type &ast_cmp::get_type() const {
    return s_type;
}

const sem_value &ast_cmp::get_value() const {
    return s_value;
}

bool ast_cmp::analyse() {
    if (semantics_child() && semantics_self()) {
        if (child_l->get_value().known && child_r->get_value().known) {
            do_cmp();
        }
        codegen();
        return true;
    } else {
        return false;
    }
}

bool ast_cmp::semantics_child() {
    return child_l->analyse() && child_r->analyse();
}

bool ast_cmp::cmp_semantics_impl(bool need_eq, bool need_cmp) {
    try {
        if (need_eq) {
            sem::assert_can_equal(child_l->get_type(), child_r->get_type());
        }
        if (need_cmp) {
            sem::assert_can_compare(child_l->get_type(), child_r->get_type());
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
