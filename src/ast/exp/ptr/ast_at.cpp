#include "sem/val/sem_id.h"
#include "sem/exception/sem_exception.h"
#include "ast/exp/ptr/ast_at.h"

ast_at::ast_at(ast_id *id) : id(id), s_type({false}), s_value({false}) {}

ast_at::~ast_at() {
    delete id;
}

const sem_type &ast_at::get_type() const {
    return s_type;
}

const sem_value &ast_at::get_value() const {
    return s_value;
}

bool ast_at::semantics_child() {
    return id->analyse();
}

bool ast_at::semantics_self() {
    try {
        sem::assert_is_variable(id->get_id());

        s_type = id->get_type();
        s_type.ptr++;
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_at::codegen() {
    llvm_value = id->get_llvm_mem();
}

void ast_at::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "at(\n";
    id->explain_impl(res, indent + 1);
    res += ")\n";
}
