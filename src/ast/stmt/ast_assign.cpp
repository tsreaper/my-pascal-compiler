#include "sem/type/sem_type.h"
#include "sem/stmt/sem_loop.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "ast/stmt/ast_assign.h"

ast_assign::ast_assign(ast_id *id, ast_value_node *rhs) : id(id), rhs(rhs) {}

ast_assign::~ast_assign() {
    delete id;
    delete rhs;
}

bool ast_assign::semantics_child() {
    return id->analyse(false) && rhs->analyse();
}

bool ast_assign::semantics_self() {
    try {
        sem::assert_can_assign(id->get_id(), id->get_type(), rhs->get_type());
        sem::assert_not_loop_var(id->get_id());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_assign::codegen() {
    ir_builder.CreateStore(rhs->get_llvm_value(), gen::get_mem(id->get_id()));
}

void ast_assign::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "assign(\n";
    id->explain_impl(res, indent + 1);
    rhs->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
