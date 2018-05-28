#include "gen/func/sys/gen_sys_write.h"
#include "ast/func/sys/ast_sys_write.h"

ast_sys_write::ast_sys_write(bool new_line): new_line(new_line) {}

ast_sys_write::~ast_sys_write() {
    for (auto child : param_vec) {
        delete child;
    }
}

void ast_sys_write::add_param(ast_value_node *param) {
    param_vec.emplace_back(param);
}

bool ast_sys_write::semantics_child() {
    for (auto child : param_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

bool ast_sys_write::semantics_self() {
    for (auto child : param_vec) {
        if (
                child->get_type() != built_in_type::INT_TYPE &&
                child->get_type() != built_in_type::REAL_TYPE &&
                child->get_type() != built_in_type::CHAR_TYPE
        ) {
            return false;
        }
    }
    return true;
}

void ast_sys_write::codegen() {
    gen::gen_write(param_vec, new_line);
}

void ast_sys_write::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += new_line ? "writeln" : "write";
    res += "(\n";

    for (auto child : param_vec) {
        child->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}
