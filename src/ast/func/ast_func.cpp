#include "sem/sem.h"
#include "sem/value/sem_var.h"
#include "sem/exception/sem_exception.h"
#include "ast/func/ast_func.h"

ast_func_head::ast_func_head(ast_id *name) : name(name) {
    sign.id = name->get_id();
    ret_type = {false};
}

ast_func_head::~ast_func_head() {
    delete name;
    delete type;
    for (auto child : param_name_vec) {
        delete child;
    }
    for (auto child : param_type_vec) {
        delete child;
    }
}

const std::string &ast_func_head::get_name() const {
    return name->get_id();
}

int ast_func_head::get_param_num() const {
    return (int) param_name_vec.size();
}

const std::vector<ast_id *> &ast_func_head::get_param_name_node() const {
    return param_name_vec;
}

const std::vector<ast_type_node *> &ast_func_head::get_param_type_node() const {
    return param_type_vec;
}

const sem_type &ast_func_head::get_ret_type() const {
    return ret_type;
}

const func_sign &ast_func_head::get_func_sign() const {
    return sign;
}

void ast_func_head::add_param(ast_id *param_name, ast_type_node *param_type) {
    param_name_vec.emplace_back(param_name);
    param_type_vec.emplace_back(param_type);
}

void ast_func_head::set_ret_type_node(ast_type_node *type) {
    this->type = type;
}

bool ast_func_head::analyse() {
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

        // Set function signature and return type
        for (auto child : param_type_vec) {
            sign.param_type_vec.emplace_back(child->get_type());
        }
        if (type == nullptr) {
            ret_type = built_in_type::VOID_TYPE;
        } else {
            ret_type = type->get_type();
        }

        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_func_head::explain_impl(std::string &res, int indent) const {
    name->explain_impl(res, indent);

    explain_indent(res, indent);
    res += "--- params ---\n";
    for (int i = 0; i < get_param_num(); i++) {
        param_name_vec[i]->explain_impl(res, indent);
        param_type_vec[i]->explain_impl(res, indent);
    }

    explain_indent(res, indent);
    res += "--- return type ---\n";
    if (type != nullptr) {
        type->explain_impl(res, indent);
    } else {
        explain_indent(res, indent);
        res += "no return type\n";
    }
}

ast_func_dec::ast_func_dec(ast_func_head *head) : head(head) {}

ast_func_dec::~ast_func_dec() {
    delete head;
}

bool ast_func_dec::analyse() {
    if (!head->analyse()) {
        return false;
    }
    try {
        declare_func(head->get_func_sign(), head->get_ret_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_func_dec::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "function_declaration(\n";
    head->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}

ast_func_def::ast_func_def(ast_func_head *head, ast_block *block) : head(head), block(block) {}

ast_func_def::~ast_func_def() {
    delete head;
    delete block;
}

bool ast_func_def::analyse() {
    if (!head->analyse()) {
        return false;
    }
    try {
        define_func(head->get_func_sign(), head->get_ret_type());
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }

    sem_env.push();
    int param_num = head->get_param_num();
    std::vector<ast_id *> names = head->get_param_name_node();
    std::vector<ast_type_node *> types = head->get_param_type_node();
    try {
        for (int i = 0; i < param_num; i++) {
            declare_var_id(names[i]->get_id(), types[i]->get_type());
        }
        if (head->get_ret_type() != built_in_type::VOID_TYPE) {
            // In pascal, function return value is stored in a variable with the same name as the function name
            declare_var_id(head->get_name(), head->get_ret_type());
        }
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        sem_env.pop();
        return false;
    }

    bool res = block->analyse();
    sem_env.pop();
    return res;
}

void ast_func_def::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "function_definition(\n";

    head->explain_impl(res, indent + 1);

    explain_indent(res, indent + 1);
    res += "--- body ---\n";
    block->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}
