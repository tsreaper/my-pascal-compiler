#include "sem/exception/sem_exception.h"
#include "sem/type/sem_enum_type.h"
#include "ast/type/ast_enum_type.h"

ast_enum_type::ast_enum_type(ast_id_seq *seq) : seq(seq) {}

ast_enum_type::~ast_enum_type() {
    delete seq;
}

bool ast_enum_type::semantics_child() {
    for (auto &child : seq->get_id_vec()) {
        if (!child->analyse(false)) {
            return false;
        }
    }
    return true;
}

bool ast_enum_type::semantics_self() {
    try {
        enum_id = sem::define_enum_type(seq->get_id_vec());
        s_type = {true, type_group::ENUM, enum_id};
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_enum_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "enum_type(\n";
    seq->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
