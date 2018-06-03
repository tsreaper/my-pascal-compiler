#include "sem/exception/sem_exception.h"
#include "ast/id/ast_id_seq_with_type.h"

ast_id_seq_with_type::ast_id_seq_with_type(ast_id_seq *seq, ast_type_node *type) : seq(seq), type(type) {}

ast_id_seq_with_type::~ast_id_seq_with_type() {
    delete seq;
    delete type;
}

const std::vector<ast_id *> &ast_id_seq_with_type::get_id_vec() const {
    return seq->get_id_vec();
}

const sem_type &ast_id_seq_with_type::get_type() const {
    return type->get_type();
}

bool ast_id_seq_with_type::semantics_child() {
    return seq->analyse() && type->analyse();
}

bool ast_id_seq_with_type::semantics_self() {
    try {
        sem::assert_is_type(type->get_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_id_seq_with_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "id_sequence_with_type(\n";

    seq->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- type ---\n";
    type->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}
