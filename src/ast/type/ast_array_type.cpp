#include "sem/type/sem_array_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/type/ast_array_type.h"

ast_array_type::~ast_array_type() {
    for (auto child : range_vec) {
        delete child;
    }
    delete ele_type;
}

void ast_array_type::append_range(ast_range_type *range) {
    range_vec.emplace_back(range);
}

void ast_array_type::set_ele_type(ast_type_node *ele_type) {
    this->ele_type = ele_type;
}

bool ast_array_type::semantics_child() {
    for (auto child : range_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return ele_type->analyse();
}

bool ast_array_type::semantics_self() {
    try {
        sem::assert_is_type(ele_type->get_type());

        std::vector<int> v;
        for (auto child : range_vec) {
            v.emplace_back(child->get_type().id);
        }
        sem_type s_ele_type = ele_type->get_type();

        // Element type may be another array type, so flatten that type.
        if (ele_type->get_type().tg == type_group::ARRAY) {
            const sem_array_type &a_t = sem::get_array_type_by_idx(ele_type->get_type().id);
            v.insert(v.end(), a_t.range_vec.begin(), a_t.range_vec.end());
            s_ele_type = a_t.ele_type;
        }

        sem_array_type array_type = {s_ele_type, (int) v.size(), v};
        type_id = sem::get_or_define_array_type(array_type);
        s_type = {true, type_group::ARRAY, type_id};
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_array_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "array_type(\n";

    for (auto child : range_vec) {
        child->explain_impl(res, indent + 1);
    }
    explain_indent(res, indent + 1);
    res += "--- element type ---\n";
    ele_type->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}
