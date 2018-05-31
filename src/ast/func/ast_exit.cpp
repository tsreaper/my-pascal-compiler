#include "gen/gen.h"
#include "gen/func/gen_func.h"
#include "ast/func/ast_exit.h"

void ast_exit::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "exit()\n";
}

void ast_exit::codegen() {
    gen::gen_exit();
    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(llvm_context, "exit_cont", func);
    ir_builder.SetInsertPoint(bb);
}
