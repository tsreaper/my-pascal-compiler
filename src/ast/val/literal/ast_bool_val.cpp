#include "gen/val/gen_literal.h"
#include "ast/val/literal/ast_bool_val.h"

ast_bool_val::ast_bool_val(bool value) : value(value) {
    s_type = built_in_type::BOOL_VAL;
    s_value = {true, {.boo = value}};
}

void ast_bool_val::codegen() {
    llvm_value = gen::get_llvm_bool(s_value);
}

void ast_bool_val::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "bool(" + std::to_string(value) + ")\n";
}
