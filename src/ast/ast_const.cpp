#include "env/env_id.h"
#include "ast/ast_id.h"
#include "ast/ast_const.h"

ast_const_def::ast_const_def(ast_id *id, ast_value_node *value) : id(id), value(value) {}

ast_const_def::~ast_const_def() {
    delete id;
    delete value;
}

bool ast_const_def::analyse() {
    if (id->analyse() && value->analyse()) {
        if (define_const_id(id->get_id(), value->get_type(), value->get_value())) {
            return true;
        } else {
            PRINT_ERROR_LINENO;
            return false;
        }
    } else {
        return false;
    }
}

void ast_const_def::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "constant_definition(\n";

    id->explain_impl(res, indent + 1);
    value->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

ast_const_def_seq::~ast_const_def_seq() {
    for (auto child : const_def_vec) {
        delete child;
    }
}

void ast_const_def_seq::add_const_def(ast_const_def *def) {
    const_def_vec.emplace_back(def);
}

bool ast_const_def_seq::analyse() {
    for (auto it = const_def_vec.rbegin(); it != const_def_vec.rend(); it++) {
        if (!(*it)->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_const_def_seq::explain_impl(std::string &res, int indent) const {
    for (auto it = const_def_vec.rbegin(); it != const_def_vec.rend(); it++) {
        (*it)->explain_impl(res, indent);
    }
}

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
