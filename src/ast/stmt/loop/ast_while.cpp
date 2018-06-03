#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "ast/stmt/loop/ast_while.h"

ast_while::ast_while(ast_value_node *cond, ast_node *body) : cond(cond), body(body) {}

ast_while::~ast_while() {
    delete cond;
    delete body;
}

llvm::BasicBlock *ast_while::get_continue_block() const {
    return cond_bb;
}

llvm::BasicBlock *ast_while::get_break_block() const {
    return cont_bb;
}

#define ENV_POP { \
    gen_env.get_loop_env().pop(); \
    sem_env.get_loop_env().pop(); \
}

bool ast_while::analyse() {
    codegen_before();

    if (!semantics_cond()) {
        return false;
    }
    codegen_cond();

    sem_env.get_loop_env().push();
    gen_env.get_loop_env().push(this);

    if (!semantics_body()) {
        ENV_POP;
        return false;
    }
    codegen_body();

    ENV_POP;
    return true;
}

void ast_while::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "while(\n";

    explain_indent(res, indent + 1);
    res += "--- condition ---\n";
    cond->explain_impl(res, indent + 1);

    explain_indent(res, indent + 1);
    res += "--- body ---\n";
    body->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

bool ast_while::semantics_cond() {
    if (!cond->analyse()) {
        return false;
    }
    try {
        if (cond->get_type() != built_in_type::BOOL_TYPE) {
            throw sem_exception("semantics error, must be a boolean expression");
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

bool ast_while::semantics_body() {
    return body->analyse();
}

void ast_while::codegen_before() {
    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    cond_bb = llvm::BasicBlock::Create(llvm_context, "while_cond", func);
    body_bb = llvm::BasicBlock::Create(llvm_context, "while_body", func);
    cont_bb = llvm::BasicBlock::Create(llvm_context, "while_cont", func);

    ir_builder.CreateBr(cond_bb);
    ir_builder.SetInsertPoint(cond_bb);
}

void ast_while::codegen_cond() {
    ir_builder.CreateCondBr(cond->get_llvm_value(), body_bb, cont_bb);
    ir_builder.SetInsertPoint(body_bb);
}

void ast_while::codegen_body() {
    ir_builder.CreateBr(cond_bb);
    ir_builder.SetInsertPoint(cont_bb);
}
