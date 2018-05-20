#include "env/env_type.h"
#include "ast/ast_type.h"

ast_type_def::ast_type_def(ast_id *id, ast_type_node *type) : id(id), type(type) {}

ast_type_def::~ast_type_def() {
    delete id;
    delete type;
}

bool ast_type_def::analyse() {
    if (id->analyse() && type->analyse()) {
        if (define_type_id(id->get_id(), type->get_type())) {
            return true;
        } else {
            PRINT_ERROR_LINENO;
            return false;
        }
    } else {
        return false;
    }
}

void ast_type_def::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "type_definition(\n";

    id->explain_impl(res, indent + 1);
    type->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

ast_type_def_seq::~ast_type_def_seq() {
    for (auto child : type_def_vec) {
        delete child;
    }
}

void ast_type_def_seq::add_type_def(ast_type_def *def) {
    type_def_vec.emplace_back(def);
}

bool ast_type_def_seq::analyse() {
    for (auto it = type_def_vec.rbegin(); it != type_def_vec.rend(); it++) {
        if (!(*it)->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_type_def_seq::explain_impl(std::string &res, int indent) const {
    for (auto it = type_def_vec.rbegin(); it != type_def_vec.rend(); it++) {
        (*it)->explain_impl(res, indent);
    }
}

// ======= int =======

env_type ast_bti_int::get_type() const {
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

env_type ast_bti_real::get_type() const {
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

env_type ast_bti_char::get_type() const {
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

env_type ast_bti_bool::get_type() const {
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

env_type ast_bti_str::get_type() const {
    return {true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::STR};
}

bool ast_bti_str::analyse() {
    return true;
}

void ast_bti_str::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string_type()\n";
}
