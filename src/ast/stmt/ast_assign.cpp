#include "sem/type/sem_type.h"
#include "sem/stmt/sem_assign.h"
#include "sem/stmt/sem_loop.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "ast/stmt/ast_assign.h"

ast_assign::ast_assign(ast_lhs *lhs, ast_value_node *rhs) : lhs(lhs), rhs(rhs) {}

ast_assign::~ast_assign() {
    delete lhs;
    delete rhs;
}

bool ast_assign::semantics_child() {
    return lhs->analyse(false) && rhs->analyse();
}

bool ast_assign::semantics_self() {
    try {
        sem::assert_can_assign(lhs, rhs->get_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_assign::codegen() {
    ir_builder.CreateStore(rhs->get_llvm_value(), lhs->get_llvm_mem());
}

void ast_assign::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "assign(\n";
    lhs->explain_impl(res, indent + 1);
    rhs->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
