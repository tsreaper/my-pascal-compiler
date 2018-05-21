#include "sem/id/sem_id.h"
#include "ast/id/ast_id.h"

ast_id::ast_id(const char *id) : id(id) {}

const sem_type &ast_id::get_type() const {
    return get_id_type(id);
}

const sem_value &ast_id::get_value() const {
    return get_id_value(id);
}

const std::string &ast_id::get_id() const {
    return id;
}

bool ast_id::analyse() {
    return true;
}

void ast_id::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "id(" + id + ")\n";
}
