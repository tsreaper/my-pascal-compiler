#include "ast/type/builtin/ast_char_type.h"

ast_char_type::ast_char_type() {
    s_type = {true, type_group::BUILT_IN, built_in_type::CHAR};
}

void ast_char_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "char_type()\n";
}
