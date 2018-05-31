#include "sem/label/sem_label.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/label/gen_label.h"
#include "ast/stmt/ast_lab_stmt.h"

ast_lab_stmt::ast_lab_stmt(int label, ast_node *stmt) : label(label), stmt(stmt) {}

ast_lab_stmt::~ast_lab_stmt() {
    delete stmt;
}

void ast_lab_stmt::explain_impl(std::string &res, int indent) const {
    res += "label(" + std::to_string(label) + ")\n";
    stmt->explain_impl(res, indent);
}

bool ast_lab_stmt::analyse() {
    if (!semantics_self()) {
        return false;
    }
    codegen();

    return semantics_child();
}

bool ast_lab_stmt::semantics_child() {
    return stmt->analyse();
}

bool ast_lab_stmt::semantics_self() {
    try {
        sem::use_label(label);
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_lab_stmt::codegen() {
    llvm::BasicBlock *bb = gen::get_block(label);
    if (bb == nullptr) {
        llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
        bb = llvm::BasicBlock::Create(llvm_context, "label_" + std::to_string(label), func);
        gen::set_block(label, bb);
    }
    ir_builder.CreateBr(bb);
    ir_builder.SetInsertPoint(bb);
}
