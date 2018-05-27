#include "ast/type/builtin/ast_str_type.h"

ast_str_type::ast_str_type() {
    s_type = {true, type_group::BUILT_IN, built_in_type::STR};
}

void ast_str_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string_type()\n";
}
