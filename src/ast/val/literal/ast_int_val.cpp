#include "gen/val/gen_literal.h"
#include "ast/val/literal/ast_int_val.h"

ast_int_val::ast_int_val(int value) : value(value) {
    s_type = built_in_type::INT_VAL;
    s_value = {true, {.num = value}};
}

void ast_int_val::codegen() {
    llvm_value = gen::get_llvm_int(s_value);
}

void ast_int_val::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "int(" + std::to_string(value) + ")\n";
}
