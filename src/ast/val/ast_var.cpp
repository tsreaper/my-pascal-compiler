#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "gen/val/gen_id.h"
#include "ast/val/ast_var.h"

ast_var_dec::ast_var_dec(ast_type_node *type) : type(type) {}

ast_var_dec::~ast_var_dec() {
    for (auto &child : id_vec) {
        delete child;
    }
    delete type;
}

void ast_var_dec::add_id(ast_id *id) {
    id_vec.emplace_back(id);
}

bool ast_var_dec::semantics_child() {
    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        if (!(*it)->analyse(false)) {
            return false;
        }
    }
    return type->analyse();
}

bool ast_var_dec::semantics_self() {
    for (auto it = id_vec.rbegin(); it != id_vec.rend(); it++) {
        try {
            sem::set_id_type((*it)->get_id(), type->get_type());
        } catch (const sem_exception &e) {
            PRINT_ERROR_MSG(e);
            return false;
        }
    }
    return true;
}

void ast_var_dec::codegen() {
    for (auto &child : id_vec) {
        gen::declare_id(child->get_id(), type->get_type());
    }
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
    for (auto &child : var_dec_vec) {
        delete child;
    }
}

void ast_var_dec_seq::add_var_dec(ast_var_dec *dec) {
    var_dec_vec.emplace_back(dec);
}

bool ast_var_dec_seq::semantics_child() {
    for (auto &child : var_dec_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_var_dec_seq::explain_impl(std::string &res, int indent) const {
    for (auto &child : var_dec_vec) {
        child->explain_impl(res, indent);
    }
}
