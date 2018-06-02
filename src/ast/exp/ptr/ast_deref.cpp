#include "sem/val/sem_id.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "ast/exp/ptr/ast_deref.h"

ast_deref::ast_deref(ast_value_node *ptr) : ptr(ptr), s_type({false}), s_value({false}) {}

ast_deref::~ast_deref() {
    delete ptr;
}

const sem_type &ast_deref::get_type() const {
    return s_type;
}

const sem_value &ast_deref::get_value() const {
    return s_value;
}

llvm::Value *ast_deref::get_llvm_mem() const {
    return ptr->get_llvm_value();
}

bool ast_deref::semantics_child() {
    return ptr->analyse();
}

bool ast_deref::semantics_self() {
    try {
        const sem_type &t = ptr->get_type();
        if (t.is_type || t.ptr <= 0) {
            throw sem_exception("semantics error, trying to dereference a non-pointer");
        }

        s_type = t;
        s_type.ptr--;
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_deref::codegen() {
    llvm_value = ir_builder.CreateLoad(ptr->get_llvm_value(), "deref_tmp");
}

void ast_deref::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "dereference(\n";
    ptr->explain_impl(res, indent + 1);
    res += ")\n";
}
