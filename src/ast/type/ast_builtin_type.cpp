#include "ast/type/ast_builtin_type.h"

// ======= int =======

sem_type ast_bti_int::get_type() const {
    return {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::INT};
}

bool ast_bti_int::analyse() {
    return true;
}

void ast_bti_int::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "int_type()\n";
}

// ======= real =======

sem_type ast_bti_real::get_type() const {
    return {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::REAL};
}

bool ast_bti_real::analyse() {
    return true;
}

void ast_bti_real::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "real_type()\n";
}

// ======= char =======

sem_type ast_bti_char::get_type() const {
    return {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::CHAR};
}

bool ast_bti_char::analyse() {
    return true;
}

void ast_bti_char::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "char_type()\n";
}

// ======= bool =======

sem_type ast_bti_bool::get_type() const {
    return {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::BOOL};
}

bool ast_bti_bool::analyse() {
    return true;
}

void ast_bti_bool::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "bool_type()\n";
}

// ======= string =======

sem_type ast_bti_str::get_type() const {
    return {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::STR};
}

bool ast_bti_str::analyse() {
    return true;
}

void ast_bti_str::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string_type()\n";
}
