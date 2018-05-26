#include "ast/type/ast_builtin_type.h"

const sem_type &ast_builtin_type::get_type() const {
    return s_type;
}

// ======= int =======

ast_bti_int::ast_bti_int() {
    s_type = {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::INT};
}

void ast_bti_int::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "int_type()\n";
}

// ======= real =======

ast_bti_real::ast_bti_real() {
    s_type = {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::REAL};
}

void ast_bti_real::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "real_type()\n";
}

// ======= char =======

ast_bti_char::ast_bti_char() {
    s_type = {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::CHAR};
}

void ast_bti_char::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "char_type()\n";
}

// ======= bool =======

ast_bti_bool::ast_bti_bool() {
    s_type = {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::BOOL};
}

void ast_bti_bool::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "bool_type()\n";
}

// ======= string =======

ast_bti_str::ast_bti_str() {
    s_type = {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::STR};
}

void ast_bti_str::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string_type()\n";
}
