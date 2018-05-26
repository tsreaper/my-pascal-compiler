#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/stmt/ast_assign.h"

ast_assign::ast_assign(ast_id *id, ast_type_node *rhs) : id(id), rhs(rhs) {}

ast_assign::~ast_assign() {
    delete id;
    delete rhs;
}

bool ast_assign::semantics_child() {
    return (code_id = id->analyse()) != nullptr && (code_rhs = rhs->analyse()) != nullptr;
}

bool ast_assign::semantics_self() {
    try {
        assert_can_assign(id->get_type(), rhs->get_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_assign::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "assign(\n";
    id->explain_impl(res, indent + 1);
    rhs->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
