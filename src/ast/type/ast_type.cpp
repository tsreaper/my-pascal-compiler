#include "sem/exception/sem_exception.h"
#include "sem/type/sem_type.h"
#include "ast/type/ast_type.h"

ast_type_def::ast_type_def(ast_id *id, ast_type_node *type) : id(id), type(type) {}

ast_type_def::~ast_type_def() {
    delete id;
    delete type;
}

bool ast_type_def::semantics_child() {
    return id->analyse() != nullptr && type->analyse() != nullptr;
}

bool ast_type_def::semantics_self() {
    try {
        define_type_id(id->get_id(), type->get_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_type_def::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "type_definition(\n";

    id->explain_impl(res, indent + 1);
    type->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

ast_type_def_seq::~ast_type_def_seq() {
    for (auto child : type_def_vec) {
        delete child;
    }
}

void ast_type_def_seq::add_type_def(ast_type_def *def) {
    type_def_vec.emplace_back(def);
}

bool ast_type_def_seq::semantics_child() {
    for (auto child : type_def_vec) {
        if (child->analyse() == nullptr) {
            return false;
        }
    }
    return true;
}

void ast_type_def_seq::explain_impl(std::string &res, int indent) const {
    for (auto child : type_def_vec) {
        child->explain_impl(res, indent);
    }
}
