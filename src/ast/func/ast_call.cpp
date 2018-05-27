#include "sem/exception/sem_exception.h"
#include "gen/val/gen_literal.h"
#include "ast/func/ast_call.h"

ast_call::ast_call(ast_id *id) : id(id), s_type({false}), s_value({false}) {}

ast_call::~ast_call() {
    delete id;
}

const sem_type &ast_call::get_type() const {
    return s_type;
}

const sem_value &ast_call::get_value() const {
    return s_value;
}

void ast_call::add_param(ast_type_node *param) {
    param_vec.emplace_back(param);
}

bool ast_call::semantics_child() {
    if (!id->analyse()) {
        return false;
    }
    for (auto child : param_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

bool ast_call::semantics_self() {
    try {
        for (auto child : param_vec) {
            if (child->get_type().is_type) {
                throw sem_exception("semantics error, procedure/function parameters cannot be a type");
            }
        }

        // Make function signature;
        sign.id = id->get_id();
        for (auto child : param_vec) {
            sign.param_type_vec.emplace_back(child->get_type());
        }

        s_type = sem::get_ret_type(sign);
        s_type.is_type = false;
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_call::codegen() {
    // TODO remove place holder
    llvm_value = gen::get_llvm_int(sem_value{true, {.num = 0}});
}

void ast_call::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "function_call(\n";

    id->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- param ---\n";
    for (auto child : param_vec) {
        child->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}
