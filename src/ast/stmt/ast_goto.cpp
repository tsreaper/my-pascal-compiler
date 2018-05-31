#include "sem/label/sem_label.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/label/gen_label.h"
#include "ast/stmt/ast_goto.h"

ast_goto::ast_goto(int label) : label(label) {}

void ast_goto::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "goto(" + std::to_string(label) + ")\n";
}

bool ast_goto::semantics_self() {
    try {
        sem::need_label(label);
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_goto::codegen() {
    llvm::BasicBlock *bb = gen::get_block(label);
    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    if (bb == nullptr) {
        bb = llvm::BasicBlock::Create(llvm_context, "label_" + std::to_string(label), func);
        gen::set_block(label, bb);
    }
    ir_builder.CreateBr(bb);

    llvm::BasicBlock *cont_bb = llvm::BasicBlock::Create(llvm_context, "goto_cont", func);
    ir_builder.SetInsertPoint(cont_bb);
}
