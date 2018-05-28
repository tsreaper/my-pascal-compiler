#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "ast/func/ast_func_def.h"

ast_func_def::ast_func_def(ast_func_head *head, ast_block *block) : head(head), block(block) {}

ast_func_def::~ast_func_def() {
    delete head;
    delete block;
}

#define ENV_POP { \
    gen_env.pop(); \
    sem_env.pop(); \
}

bool ast_func_def::analyse() {
    if (!semantics_child()) {
        return false;
    }

    codegen_phase1();
    sem_env.push();
    gen_env.push();

    if (!semantics_self()) {
        ENV_POP;
        return false;
    }

    codegen_phase2();

    if (!block->analyse()) {
        ENV_POP;
        return false;
    }

    codegen_phase3();
    ENV_POP;
    return true;
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
            sem::set_id_type(head->get_name(), head->get_ret_type());
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
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

void ast_func_def::codegen_phase1() {
    old_bb = ir_builder.GetInsertBlock();
    gen::define_func(head->get_func_sign(), head->get_ret_type());
}

void ast_func_def::codegen_phase2() {
    int param_num = head->get_param_num();
    std::vector<ast_id *> names = head->get_param_name_node();
    std::vector<ast_type_node *> types = head->get_param_type_node();

    llvm::Function *func = gen::get_func(head->get_func_sign());
    auto arg_it = func->arg_begin();
    for (int i = 0; i < param_num; i++) {
        gen::declare_id(names[i]->get_id(), types[i]->get_type());

        arg_it->setName(names[i]->get_id());
        ir_builder.CreateStore(arg_it, gen::get_mem(names[i]->get_id()));
        arg_it++;
    }

    if (head->get_ret_type() != built_in_type::VOID_TYPE) {
        // In pascal, function return val is stored in a variable with the same name as the function name
        gen::declare_id(head->get_name(), head->get_ret_type());
    }
}

void ast_func_def::codegen_phase3() {
    if (head->get_ret_type() != built_in_type::VOID_TYPE) {
        llvm::Value *ret = ir_builder.CreateLoad(gen::get_mem(head->get_name()), "ret");
        ir_builder.CreateRet(ret);
    } else {
        ir_builder.CreateRetVoid();
    }
    ir_builder.SetInsertPoint(old_bb);
}
