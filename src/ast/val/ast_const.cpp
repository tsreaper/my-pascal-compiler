#include <llvm/IR/Instructions.h>

#include "sem/exception/sem_exception.h"
#include "sem/val/sem_const.h"
#include "ast/val/ast_id.h"
#include "ast/val/ast_const.h"

ast_const_def::ast_const_def(ast_id *id, ast_value_node *value) : id(id), value(value) {}

ast_const_def::~ast_const_def() {
    delete id;
    delete value;
}

bool ast_const_def::semantics_child() {
    return id->analyse(false) && value->analyse();
}

bool ast_const_def::semantics_self() {
    try {
        sem::define_const_id(id->get_id(), value->get_type(), value->get_value());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_const_def::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "constant_definition(\n";

    id->explain_impl(res, indent + 1);
    value->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

ast_const_def_seq::~ast_const_def_seq() {
    for (auto &child : const_def_vec) {
        delete child;
    }
}

void ast_const_def_seq::add_const_def(ast_const_def *def) {
    const_def_vec.emplace_back(def);
}

bool ast_const_def_seq::semantics_child() {
    for (auto &child : const_def_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_const_def_seq::explain_impl(std::string &res, int indent) const {
    for (auto &child : const_def_vec) {
        child->explain_impl(res, indent);
    }
}
