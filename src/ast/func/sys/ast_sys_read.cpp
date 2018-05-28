#include "gen/func/sys/gen_sys_read.h"
#include "ast/func/sys/ast_sys_read.h"

ast_sys_read::~ast_sys_read() {
    for (auto child : param_vec) {
        delete child;
    }
}

void ast_sys_read::add_param(ast_id *param) {
    param_vec.emplace_back(param);
}

bool ast_sys_read::semantics_child() {
    for (auto child : param_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

bool ast_sys_read::semantics_self() {
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

void ast_sys_read::codegen() {
    gen::gen_read(param_vec);
}

void ast_sys_read::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "read(\n";

    for (auto child : param_vec) {
        child->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}
