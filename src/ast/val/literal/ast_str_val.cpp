#include "ast/val/literal/ast_str_val.h"

ast_str_val::ast_str_val(const char *value) : value(value) {
    s_type = built_in_type::STR_VAL;
    s_value = {true};
    s_value.value.str = &this->value;
}

void ast_str_val::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string(" + value + ")\n";
}
