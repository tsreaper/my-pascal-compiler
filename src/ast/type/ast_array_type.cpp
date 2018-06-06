#include "sem/type/sem_array_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/type/ast_array_type.h"

ast_array_type::~ast_array_type() {
    for (auto &child : range_vec) {
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
    for (auto &child : range_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return ele_type->analyse();
}

bool ast_array_type::semantics_self() {
    try {
        for (auto &child : range_vec) {
            const sem_range_type &r_t = sem::get_range_type_by_idx(child->get_type().id);
            if (sem::get_range_length(r_t) <= 1) {
                throw sem_exception("semantics error, length of array must be greater than 1");
            }
        }
        sem::assert_is_type(ele_type->get_type());

        sem_array_type array_type = sem::make_array_type(range_vec, ele_type);
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

    for (auto &child : range_vec) {
        child->explain_impl(res, indent + 1);
    }
    explain_indent(res, indent + 1);
    res += "--- element type ---\n";
    ele_type->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}
