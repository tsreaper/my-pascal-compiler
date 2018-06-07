#include "sem/type/sem_type.h"
#include "sem/exception/sem_exception.h"
#include "gen/id/gen_id.h"
#include "ast/val/ast_var.h"

ast_var_dec::ast_var_dec(ast_id_seq_with_type *seq, ast_value_node *init_val) : seq(seq) {
    if (init_val != nullptr) {
        assign_node = new ast_assign(seq->get_id_vec()[0], init_val);
    } else {
        assign_node = nullptr;
    }
}

ast_var_dec::~ast_var_dec() {
    delete seq;
    delete assign_node;
}

bool ast_var_dec::analyse() {
    if (semantics_child() && semantics_self()) {
        codegen();
        return assign_node == nullptr || assign_node->analyse();
    } else {
        return false;
    }
}

bool ast_var_dec::semantics_child() {
    return seq->analyse();
}

bool ast_var_dec::semantics_self() {
    for (auto child : seq->get_id_vec()) {
        try {
            sem::set_id_type(child->get_id(), seq->get_type());
            if (seq->get_id_vec().size() > 1 && assign_node != nullptr) {
                throw sem_exception("semantics error, only one variable can be initialized at a time");
            }
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

    if (assign_node != nullptr) {
        assign_node->explain_impl(res, indent);
    }
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
