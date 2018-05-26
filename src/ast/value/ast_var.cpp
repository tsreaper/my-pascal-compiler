#include "sem/exception/sem_exception.h"
#include "sem/value/sem_var.h"
#include "ast/value/ast_var.h"

ast_var_dec::ast_var_dec(ast_type_node *type) : type(type) {}

ast_var_dec::~ast_var_dec() {
    for (auto child : id_vec) {
        delete child;
    }
    delete type;
}

void ast_var_dec::add_id(ast_id *id) {
    id_vec.emplace_back(id);
}

bool ast_var_dec::semantics_child() {
    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        if ((*it)->analyse() == nullptr) {
            return false;
        }
    }
    return type->analyse() != nullptr;
}

bool ast_var_dec::semantics_self() {
    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        try {
            declare_var_id((*it)->get_id(), type->get_type());
        } catch (const sem_exception &e) {
            PRINT_ERROR_MSG(e);
            return false;
        }
    }
    return true;
}

void ast_var_dec::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "variable_declaration(\n";

    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        (*it)->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent + 1);
    res += "--- type ---\n";
    type->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

ast_var_dec_seq::~ast_var_dec_seq() {
    for (auto child : var_dec_vec) {
        delete child;
    }
}

void ast_var_dec_seq::add_var_dec(ast_var_dec *dec) {
    var_dec_vec.emplace_back(dec);
}

bool ast_var_dec_seq::semantics_child() {
    for (auto child : var_dec_vec) {
        llvm::Value *code = child->analyse();
        if (code == nullptr) {
            return false;
        }
        code_var_dec_vec.emplace_back(code);
    }
    return true;
}

void ast_var_dec_seq::explain_impl(std::string &res, int indent) const {
    for (auto child : var_dec_vec) {
        child->explain_impl(res, indent);
    }
}
