#include "ast/type/builtin/ast_real_type.h"

ast_real_type::ast_real_type() {
    s_type = {true, type_group::BUILT_IN, built_in_type::REAL};
}

void ast_real_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "real_type()\n";
}
