#include "ast/type/builtin/ast_int_type.h"

ast_int_type::ast_int_type() {
    s_type = {true, type_group::BUILT_IN, built_in_type::INT};
}

void ast_int_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "int_type()\n";
}
