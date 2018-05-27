#include "ast/type/builtin/ast_bool_type.h"

ast_bool_type::ast_bool_type() {
    s_type = {true, type_group::BUILT_IN, built_in_type::BOOL};
}

void ast_bool_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "bool_type()\n";
}
