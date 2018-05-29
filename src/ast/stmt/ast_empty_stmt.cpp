#include "ast/stmt/ast_empty_stmt.h"

void ast_empty_stmt::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "empty_stmt()\n";
}
