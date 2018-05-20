#include "ast/value/ast_literal.h"

// ======= int =======

ast_lit_int::ast_lit_int(int value) : value(value) {}

env_type ast_lit_int::get_type() const {
    return {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::INT};
}

env_value ast_lit_int::get_value() const {
    return {true, {.num = value}};
}

bool ast_lit_int::analyse() {
    return true;
}

void ast_lit_int::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "int(" + std::to_string(value) + ")\n";
}

// ======= real =======

ast_lit_real::ast_lit_real(double value) : value(value) {}

env_type ast_lit_real::get_type() const {
    return {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::REAL};
}

env_value ast_lit_real::get_value() const {
    return {true, {.real = value}};
}

bool ast_lit_real::analyse() {
    return true;
}

void ast_lit_real::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "real(" + std::to_string(value) + ")\n";
}

// ======= char =======

ast_lit_char::ast_lit_char(char value) : value(value) {}

env_type ast_lit_char::get_type() const {
    return {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::CHAR};
}

env_value ast_lit_char::get_value() const {
    return {true, {.chr = value}};
}

bool ast_lit_char::analyse() {
    return true;
}

void ast_lit_char::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "char(" + std::to_string(value) + ")\n";
}

// ======= bool =======

ast_lit_bool::ast_lit_bool(bool value) : value(value) {}

env_type ast_lit_bool::get_type() const {
    return {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::BOOL};
}

env_value ast_lit_bool::get_value() const {
    return {true, {.boo = value}};
}

bool ast_lit_bool::analyse() {
    return true;
}

void ast_lit_bool::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "bool(" + std::to_string(value) + ")\n";
}

// ======= string =======

ast_lit_str::ast_lit_str(const char *value) : value(value) {}

env_type ast_lit_str::get_type() const {
    return {true, meta_group::CONST, type_group::BUILT_IN, built_in_type::STR};
}

env_value ast_lit_str::get_value() const {
    // Can't write {true, {.str = &value}}. Don't know why.
    env_value res = {true, {}};
    res.value.str = &value;
    return res;
}

bool ast_lit_str::analyse() {
    return true;
}

void ast_lit_str::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string(" + value + ")\n";
}
