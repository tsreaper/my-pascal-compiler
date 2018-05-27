#include "gen/val/gen_literal.h"
#include "ast/val/literal/ast_char_val.h"

ast_char_val::ast_char_val(char value) : value(value) {
    s_type = built_in_type::CHAR_VAL;
    s_value = {true, {.chr = value}};
}

void ast_char_val::codegen() {
    llvm_value = gen::get_llvm_char(s_value);
}

void ast_char_val::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "char(" + std::to_string(value) + ")\n";
}
