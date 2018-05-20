#include "ast_label.h"

ast_label_dec_part::ast_label_dec_part(int label, ast_node *next_dec) : label(label), next_dec(next_dec) {}

ast_label_dec_part::~ast_label_dec_part() {
    delete next_dec;
}

bool ast_label_dec_part::check() {
    return next_dec->check();
}

void ast_label_dec_part::explain_impl(std::string &res, int indent) {
    explain_indent(res, indent);
    res += "label_declaration(" + std::to_string(label) + ")\n";

    next_dec->explain_impl(res, indent);
}
