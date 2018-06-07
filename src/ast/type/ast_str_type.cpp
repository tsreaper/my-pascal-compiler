#include "sem/type/sem_str_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/type/ast_str_type.h"

ast_str_type::ast_str_type(ast_value_node *len_node) : len_node(len_node) {}

bool ast_str_type::semantics_child() {
    return len_node == nullptr || len_node->analyse();
}

bool ast_str_type::semantics_self() {
    try {
        if (len_node == nullptr) {
            len = DEFAULT_STR_LEN;
        } else {
            if (len_node->get_type() != built_in_type::INT_TYPE) {
                throw sem_exception("semantics error, length of string must be integer");
            }
            if (!len_node->get_value().known) {
                throw sem_exception("semantics error, length of string must be constant");
            }
            len = len_node->get_value().value.num;
        }

        if (len <= 0) {
            throw sem_exception("semantics error, length of string must be positive");
        }
        s_type = sem::get_str_type_by_len(len);
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_str_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string_type(" + std::to_string(len) + ")\n";
}
