#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "gen/id/gen_id.h"
#include "ast/val/ast_var.h"

ast_var_dec::ast_var_dec(ast_id_seq_with_type *seq) : seq(seq) {}

ast_var_dec::~ast_var_dec() {
    delete seq;
}

bool ast_var_dec::semantics_child() {
    return seq->analyse();
}

bool ast_var_dec::semantics_self() {
    for (auto child : seq->get_id_vec()) {
        try {
            sem::set_id_type(child->get_id(), seq->get_type());
        } catch (const sem_exception &e) {
            PRINT_ERROR_MSG(e);
            return false;
        }
    }
    return true;
}

void ast_var_dec::codegen() {
    for (auto &child : seq->get_id_vec()) {
        gen::declare_id(child->get_id(), seq->get_type());
    }
}

void ast_var_dec::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "variable_declaration(\n";
    seq->explain_impl(res, indent + 1);
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
