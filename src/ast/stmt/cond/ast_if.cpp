#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "ast/stmt/cond/ast_if.h"

ast_if::ast_if(
        ast_value_node *cond, ast_node *then_stmt, ast_node *else_stmt
) : cond(cond), then_stmt(then_stmt), else_stmt(else_stmt) {}

ast_if::~ast_if() {
    delete cond;
    delete then_stmt;
    delete else_stmt;
}

bool ast_if::analyse() {
    if (!semantics_cond()) {
        return false;
    }
    codegen_cond();

    if (!semantics_then()) {
        return false;
    }
    codegen_then();

    if (!semantics_else()) {
        return false;
    }
    codegen_else();

    return true;
}

void ast_if::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "if(\n";

    cond->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- then ---\n";
    then_stmt->explain_impl(res, indent + 1);
    if (else_stmt != nullptr) {
        explain_indent(res, indent + 1);
        res += "--- else ---\n";
        else_stmt->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}

bool ast_if::semantics_cond() {
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

bool ast_if::semantics_then() {
    return then_stmt->analyse();
}

bool ast_if::semantics_else() {
    return else_stmt == nullptr || else_stmt->analyse();
}

void ast_if::codegen_cond() {
    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    then_bb = llvm::BasicBlock::Create(llvm_context, "if_then", func);
    else_bb = llvm::BasicBlock::Create(llvm_context, "if_else", func);
    cont_bb = llvm::BasicBlock::Create(llvm_context, "if_cont", func);

    ir_builder.CreateCondBr(cond->get_llvm_value(), then_bb, else_bb);
    ir_builder.SetInsertPoint(then_bb);
}

void ast_if::codegen_then() {
    ir_builder.CreateBr(cont_bb);
    ir_builder.SetInsertPoint(else_bb);
}

void ast_if::codegen_else() {
    ir_builder.CreateBr(cont_bb);
    ir_builder.SetInsertPoint(cont_bb);
}
