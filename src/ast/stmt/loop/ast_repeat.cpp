#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "ast/stmt/loop/ast_repeat.h"

ast_repeat::ast_repeat(ast_value_node *cond, ast_node *body) : cond(cond), body(body) {}

ast_repeat::~ast_repeat() {
    delete cond;
    delete body;
}

llvm::BasicBlock *ast_repeat::get_continue_block() const {
    return cond_bb;
}

llvm::BasicBlock *ast_repeat::get_break_block() const {
    return cont_bb;
}

#define ENV_POP { \
    gen_env.get_loop_env().pop(); \
    sem_env.get_loop_env().pop(); \
}

bool ast_repeat::analyse() {
    codegen_before();

    sem_env.get_loop_env().push();
    gen_env.get_loop_env().push(this);

    if (!semantics_body()) {
        ENV_POP;
        return false;
    }
    codegen_body();

    if (!semantics_cond()) {
        ENV_POP;
        return false;
    }
    codegen_cond();

    ENV_POP;
    return true;
}

void ast_repeat::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "repeat(\n";

    body->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- until ---\n";
    cond->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

bool ast_repeat::semantics_body() {
    return body->analyse();
}

bool ast_repeat::semantics_cond() {
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

void ast_repeat::codegen_before() {
    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    body_bb = llvm::BasicBlock::Create(llvm_context, "repeat_body", func);
    cond_bb = llvm::BasicBlock::Create(llvm_context, "repeat_cond", func);
    cont_bb = llvm::BasicBlock::Create(llvm_context, "repeat_cont", func);

    ir_builder.CreateBr(body_bb);
    ir_builder.SetInsertPoint(body_bb);
}

void ast_repeat::codegen_body() {
    ir_builder.CreateBr(cond_bb);
    ir_builder.SetInsertPoint(cond_bb);
}

void ast_repeat::codegen_cond() {
    llvm::Value *llvm_cond = ir_builder.CreateICmpEQ(
            cond->get_llvm_value(), gen::get_llvm_bool(sem_value{true, {.boo = true}})
    );
    ir_builder.CreateCondBr(llvm_cond, cont_bb, body_bb);
    ir_builder.SetInsertPoint(cont_bb);
}
