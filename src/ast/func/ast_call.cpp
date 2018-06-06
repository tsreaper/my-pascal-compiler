#include "sem/func/sem_call.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/func/gen_call.h"
#include "ast/func/ast_call.h"

ast_call::ast_call(ast_id *id, ast_exp_seq *param) : id(id), param(param) {}

ast_call::~ast_call() {
    delete id;
}

bool ast_call::semantics_child() {
    if (!id->analyse(false)) {
        return false;
    }
    for (auto &child : param->get_exp_vec()) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

bool ast_call::semantics_self() {
    try {
        for (auto &child : param->get_exp_vec()) {
            if (child->get_type().is_type) {
                throw sem_exception("semantics error, procedure/function parameters cannot be a type");
            }
        }

        // Make function signature;
        func_sign sign;
        sign.id = id->get_id();
        for (auto &child : param->get_exp_vec()) {
            sign.param_type_vec.emplace_back(child->get_type());
        }

        exact_fsr = sem::get_call_func_sign_ret(sign);
        s_type = exact_fsr.second;
        s_type.is_type = false;
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_call::codegen() {
    llvm_value = gen::get_func_call(exact_fsr.first, param->get_exp_vec());
}

void ast_call::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "function_call(\n";

    id->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- param ---\n";
    for (auto &child : param->get_exp_vec()) {
        child->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}
