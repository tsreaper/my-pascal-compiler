#include "ast_literal.h"

ast_int::ast_int(int value) : value(value) {}

type ast_int::value_type() {
    return type::INT;
}

bool ast_int::check() {
    return true;
}

void ast_int::explain_impl(std::string &res, int indent) {
    explain_indent(res, indent);
    res += "int(" + std::to_string(value) + ")\n";
}

ast_real::ast_real(double value) : value(value) {}

type ast_real::value_type() {
    return type::REAL;
}

bool ast_real::check() {
    return true;
}

void ast_real::explain_impl(std::string &res, int indent) {
    explain_indent(res, indent);
    res += "real(" + std::to_string(value) + ")\n";
}

ast_str::ast_str(const char *value) : value(value) {}

type ast_str::value_type() {
    return type::STR;
}

bool ast_str::check() {
    return true;
}

void ast_str::explain_impl(std::string &res, int indent) {
    explain_indent(res, indent);
    res += "string(" + value + ")\n";
}
