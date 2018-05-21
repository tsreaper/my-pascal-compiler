#include "ast/value/ast_literal.h"

const sem_type &ast_literal::get_type() const {
    return s_type;
}

const sem_value &ast_literal::get_value() const {
    return s_value;
}

// ======= int =======

ast_lit_int::ast_lit_int(int value) : value(value) {
    s_type = {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::INT};
    s_value = {true, {.num = value}};
}

bool ast_lit_int::analyse() {
    return true;
}

void ast_lit_int::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "int(" + std::to_string(value) + ")\n";
}

// ======= real =======

ast_lit_real::ast_lit_real(double value) : value(value) {
    s_type = {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::REAL};
    s_value = {true, {.real = value}};
}

bool ast_lit_real::analyse() {
    return true;
}

void ast_lit_real::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "real(" + std::to_string(value) + ")\n";
}

// ======= char =======

ast_lit_char::ast_lit_char(char value) : value(value) {
    s_type = {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::CHAR};
    s_value = {true, {.chr = value}};
}

bool ast_lit_char::analyse() {
    return true;
}

void ast_lit_char::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "char(" + std::to_string(value) + ")\n";
}

// ======= bool =======

ast_lit_bool::ast_lit_bool(bool value) : value(value) {
    s_type = {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::BOOL};
    s_value = {true, {.boo = value}};
}

bool ast_lit_bool::analyse() {
    return true;
}

void ast_lit_bool::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "bool(" + std::to_string(value) + ")\n";
}

// ======= string =======

ast_lit_str::ast_lit_str(const char *value) : value(value) {
    s_type = {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::STR};
    s_value = {true, {}};
    s_value.value.str = &this->value;
}

bool ast_lit_str::analyse() {
    return true;
}

void ast_lit_str::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string(" + value + ")\n";
}
