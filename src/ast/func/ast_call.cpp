#include "sem/exception/sem_exception.h"
#include "ast/func/ast_call.h"

ast_call::ast_call(ast_id *id) : id(id) {
    type = {false};
}

ast_call::~ast_call() {
    delete id;
}

const sem_type &ast_call::get_type() const {
    return type;
}

void ast_call::add_param(ast_type_node *param) {
    param_vec.emplace_back(param);
}

bool ast_call::semantics_child() {
    if ((code_id = id->analyse()) == nullptr) {
        return false;
    }
    for (auto child : param_vec) {
        llvm::Value *code = child->analyse();
        if (code == nullptr) {
            return false;
        }
        code_param_vec.emplace_back(code);
    }
    return true;
}

bool ast_call::semantics_self() {
    try {
        for (auto child : param_vec) {
            if (child->get_type().mg == meta_group::TYPE) {
                throw sem_exception("semantics error, procedure/function parameters cannot be a type");
            }
        }

        // Make function signature;
        sign.id = id->get_id();
        for (auto child : param_vec) {
            sign.param_type_vec.emplace_back(child->get_type());
        }

        type = get_ret_type(sign);
        type.mg = meta_group::EXP;
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
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
