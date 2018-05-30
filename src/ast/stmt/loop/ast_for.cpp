#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/exp/gen_arith.h"
#include "ast/stmt/loop/ast_for.h"

ast_for::ast_for(
        ast_id *loop_id, ast_value_node *start_val, ast_value_node *end_val, ast_node *body, bool down
) : loop_id(loop_id), start_val(start_val), end_val(end_val), body(body), down(down) {}

ast_for::~ast_for() {
    delete loop_id;
    delete start_val;
    delete end_val;
    delete body;
}

llvm::BasicBlock *ast_for::get_continue_block() const {
    return step_bb;
}

llvm::BasicBlock *ast_for::get_break_block() const {
    return cont_bb;
}

#define ENV_POP { \
    gen_env.get_loop_env().pop(); \
    sem_env.get_loop_env().pop(); \
}

bool ast_for::analyse() {
    if (!semantics_range()) {
        return false;
    }
    codegen_range();

    sem_env.get_loop_env().push(loop_id->get_id());
    gen_env.get_loop_env().push(this);

    if (!semantics_body()) {
        ENV_POP;
        return false;
    }
    codegen_body();

    ENV_POP;
    return true;
}

void ast_for::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "for(\n";

    loop_id->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- start_value ---\n";
    start_val->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- end_value---\n";
    end_val->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- body ---\n";
    body->explain_impl(res, indent + 1);

    explain_indent(res, indent);
    res += ")\n";
}

bool ast_for::semantics_range() {
    if (!loop_id->analyse(false)) {
        return false;
    }
    if (!start_val->analyse()) {
        return false;
    }
    if (!end_val->analyse()) {
        return false;
    }

    try {
        sem::assert_can_be_range(start_val->get_type(), end_val->get_type());
        sem::assert_can_assign(loop_id->get_id(), loop_id->get_type(), start_val->get_type());
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

bool ast_for::semantics_body() {
    return body->analyse();
}

void ast_for::codegen_range() {
    ir_builder.CreateStore(start_val->get_llvm_value(), gen::get_mem(loop_id->get_id()));

    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    cond_bb = llvm::BasicBlock::Create(llvm_context, "for_cond", func);
    body_bb = llvm::BasicBlock::Create(llvm_context, "for_body", func);
    step_bb = llvm::BasicBlock::Create(llvm_context, "for_step", func);
    cont_bb = llvm::BasicBlock::Create(llvm_context, "for_cont", func);

    ir_builder.CreateBr(cond_bb);
    ir_builder.SetInsertPoint(cond_bb);

    llvm::Value *llvm_load = ir_builder.CreateLoad(loop_id->get_llvm_mem());
    llvm::Value *llvm_cond = nullptr;
    if (down) {
        llvm_cond = ir_builder.CreateICmpSGE(llvm_load, end_val->get_llvm_value(), "for_cond");
    } else {
        llvm_cond = ir_builder.CreateICmpSLE(llvm_load, end_val->get_llvm_value(), "for_cond");
    }
    ir_builder.CreateCondBr(llvm_cond, body_bb, cont_bb);

    ir_builder.SetInsertPoint(body_bb);
}

void ast_for::codegen_body() {
    ir_builder.CreateBr(step_bb);
    ir_builder.SetInsertPoint(step_bb);

    llvm::Value *llvm_load = ir_builder.CreateLoad(loop_id->get_llvm_mem());
    llvm::Value *changed = nullptr;
    if (down) {
        changed = gen::gen_arith_sub_one(loop_id->get_type(), llvm_load);
    } else {
        changed = gen::gen_arith_add_one(loop_id->get_type(), llvm_load);
    }
    ir_builder.CreateStore(changed, loop_id->get_llvm_mem());
    ir_builder.CreateBr(cond_bb);

    ir_builder.SetInsertPoint(cont_bb);
}
