#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "ast/func/ast_func.h"

ast_func_head::ast_func_head(ast_id *name) : name(name), type(nullptr) {
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

bool ast_func_head::semantics_child() {
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
    return type == nullptr || type->analyse();
}

bool ast_func_head::semantics_self() {
    try {
        for (auto child : param_type_vec) {
            sem::assert_is_type(child->get_type());
        }
        if (type != nullptr) {
            sem::assert_is_type(type->get_type());
        }

        // Set function signature and return type
        sign.id = name->get_id();
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

bool ast_func_dec::semantics_child() {
    return head->analyse();
}

bool ast_func_dec::semantics_self() {
    try {
        sem::declare_func(head->get_func_sign(), head->get_ret_type());
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
    if (!semantics_child()) {
        return false;
    }

    sem_env.push();
    gen_env.push();
    bool res = semantics_self();
    gen_env.pop();
    sem_env.pop();
    return res;
}

bool ast_func_def::semantics_child() {
    if (!head->analyse()) {
        return false;
    }
    try {
        sem::define_func(head->get_func_sign(), head->get_ret_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

bool ast_func_def::semantics_self() {
    int param_num = head->get_param_num();
    std::vector<ast_id *> names = head->get_param_name_node();
    std::vector<ast_type_node *> types = head->get_param_type_node();
    try {
        for (int i = 0; i < param_num; i++) {
            sem::set_id_type(names[i]->get_id(), types[i]->get_type());
        }
        if (head->get_ret_type() != built_in_type::VOID_TYPE) {
            // In pascal, function return val is stored in a variable with the same name as the function name
            // TODO dont forget to create alloca for return value!!!
            sem::set_id_type(head->get_name(), head->get_ret_type());
        }
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }

    return block->analyse();
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
