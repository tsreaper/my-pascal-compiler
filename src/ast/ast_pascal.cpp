#include "ast_pascal.h"

ast_pascal::ast_pascal(
        ast_node *label_dec_part, ast_node *const_def_part, ast_node *type_def_part,
        ast_node *var_dec_part, ast_node *proc_func_dec_part, ast_node *compound_stm
) :
        label_dec_part(label_dec_part), const_def_part(const_def_part), type_def_part(type_def_part),
        var_dec_part(var_dec_part), proc_func_dec_part(proc_func_dec_part), compound_stm(compound_stm) {}

ast_pascal::~ast_pascal() {
    delete label_dec_part;
    delete const_def_part;
    delete type_def_part;
    delete var_dec_part;
    delete proc_func_dec_part;
    delete compound_stm;
}

bool ast_pascal::check() {
    return (
            label_dec_part->check() && const_def_part->check() && type_def_part->check() &&
            var_dec_part->check() && proc_func_dec_part->check() && compound_stm->check()
    );
}

void ast_pascal::explain_impl(std::string &res, int indent) {
    explain_indent(res, indent);
    res += "pascal(\n";

    label_dec_part->explain_impl(res, indent + 1);
    const_def_part->explain_impl(res, indent + 1);
    type_def_part->explain_impl(res, indent + 1);
    var_dec_part->explain_impl(res, indent + 1);
    proc_func_dec_part->explain_impl(res, indent + 1);
    compound_stm->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}
