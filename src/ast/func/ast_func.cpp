#include "sem/exception/sem_exception.h"
#include "sem/func/sem_func.h"
#include "ast/func/ast_func.h"

ast_func_dec::ast_func_dec(ast_id *name) : name(name) {}

ast_func_dec::~ast_func_dec() {
    delete name;
    delete type;
    for (auto child : param_name_vec) {
        delete child;
    }
    for (auto child : param_type_vec) {
        delete child;
    }
}

int ast_func_dec::get_param_num() const {
    return (int) param_name_vec.size();
}

void ast_func_dec::add_param(ast_id *param_name, ast_type_node *param_type) {
    param_name_vec.emplace_back(param_name);
    param_type_vec.emplace_back(param_type);
}

void ast_func_dec::set_ret_type(ast_type_node *type) {
    this->type = type;
}

bool ast_func_dec::analyse() {
    if (!name->analyse()) {
        return false;
    }
    for (auto child : param_name_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    for (auto child : param_type_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    if (type != nullptr && !type->analyse()) {
        return false;
    }

    try {
        for (auto child : param_type_vec) {
            assert_is_type(child->get_type());
        }
        if (type != nullptr) {
            assert_is_type(type->get_type());
        }
        declare_func(
                name->get_id(), param_type_vec,
                type == nullptr ?
                sem_type{true, meta_group::TYPE, type_group::BUILT_IN, built_in_type::VOID} :
                type->get_type()
        );
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_func_dec::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "function_declaration(\n";

    name->explain_impl(res, indent + 1);

    explain_indent(res, indent + 1);
    res += "--- params ---\n";
    for (int i = 0; i < get_param_num(); i++) {
        param_name_vec[i]->explain_impl(res, indent + 1);
        param_type_vec[i]->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent + 1);
    res += "--- return type ---\n";
    if (type != nullptr) {
        type->explain_impl(res, indent + 1);
    } else {
        explain_indent(res, indent + 1);
        res += "no return type\n";
    }

    explain_indent(res, indent);
    res += ")\n";
}
