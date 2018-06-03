#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/type/ast_ptr_type.h"

ast_ptr_type::ast_ptr_type(ast_type_node *domain) : domain(domain) {}

ast_ptr_type::~ast_ptr_type() {
    delete domain;
}

bool ast_ptr_type::semantics_child() {
    return domain->analyse();
}

bool ast_ptr_type::semantics_self() {
    try {
        sem::assert_is_type(domain->get_type());
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }

    s_type = domain->get_type();
    s_type.ptr++;
    return true;
}

void ast_ptr_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "ptr_type(\n";
    domain->explain_impl(res, indent + 1);
    res += ")\n";
}
