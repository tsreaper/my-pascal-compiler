#include <sem/val/sem_value.h>
#include "sem/type/sem_range_type.h"
#include "sem/exp/sem_cmp.h"
#include "sem/exception/sem_exception.h"
#include "ast/type/ast_range_type.h"

ast_range_type::ast_range_type(ast_value_node *low, ast_value_node *high) : low(low), high(high), s_type({false}) {}

ast_range_type::~ast_range_type() {
    delete low;
    delete high;
}

const sem_type &ast_range_type::get_type() const {
    return s_type;
}

bool ast_range_type::semantics_child() {
    return low->analyse() && high->analyse();
}

bool ast_range_type::semantics_self() {
    try {
        const sem_type &t_l = low->get_type();
        const sem_type &t_r = high->get_type();
        const sem_value &v_l = low->get_value();
        const sem_value &v_r = high->get_value();

        sem::assert_can_be_range(t_l, t_r);
        if (!v_l.known || !v_r.known) {
            throw sem_exception("semantics error, boundary of subrange must be constant");
        }
        if (!sem::do_cmp_le(t_l, t_r, v_l, v_r).value.boo) {
            throw sem_exception(
                    "semantics error, the lower boundary of subrange must not be greater than the higher boundary"
            );
        }

        sem_range_type t = {t_l, v_l, v_r};
        range_id = sem::get_or_define_range_type(t);
        s_type = {true, type_group::SUBRANGE, range_id};
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_range_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "subrange_type(\n";
    low->explain_impl(res, indent + 1);
    high->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
