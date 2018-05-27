#include "gen/val/gen_literal.h"
#include "ast/val/literal/ast_real_val.h"

ast_real_val::ast_real_val(double value) : value(value) {
    s_type = built_in_type::REAL_VAL;
    s_value = {true, {.real = value}};
}

void ast_real_val::codegen() {
    llvm_value = gen::get_llvm_real(s_value);
}

void ast_real_val::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "real(" + std::to_string(value) + ")\n";
}
