#include <cstdio>

#include "env/label/env_label.h"
#include "ast/label/ast_label.h"

ast_label_dec::ast_label_dec(int label) : label(label) {}

bool ast_label_dec::analyse() {
    if (declare_label(label)) {
        return true;
    } else {
        PRINT_ERROR_LINENO;
        return false;
    }
}

void ast_label_dec::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "label_declaration(" + std::to_string(label) + ")\n";
}

ast_label_dec_seq::~ast_label_dec_seq() {
    for (auto child : label_dec_vec) {
        delete child;
    }
}

void ast_label_dec_seq::add_label_dec(ast_label_dec *dec) {
    label_dec_vec.emplace_back(dec);
}

bool ast_label_dec_seq::analyse() {
    for (auto child : label_dec_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_label_dec_seq::explain_impl(std::string &res, int indent) const {
    for (auto child : label_dec_vec) {
        child->explain_impl(res, indent);
    }
}
