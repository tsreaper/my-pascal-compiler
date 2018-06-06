#include "sem/exp/sem_logic.h"
#include "gen/gen.h"
#include "gen/type/gen_builtin_type.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_logic.h"
#include "ast/exp/logic/ast_logic_or.h"

ast_logic_or::ast_logic_or(ast_value_node *child_l, ast_value_node *child_r) : ast_logic(child_l, child_r) {}

void ast_logic_or::codegen_l() {
    const sem_value &v = child_l->get_value();
    if (v.known) {
        if (v.value.boo) {
            s_value = {true, {.boo = true}};
            llvm_value = gen::get_llvm_bool(s_value);
        }
    } else {
        llvm_tmp = ir_builder.CreateAlloca(gen::get_llvm_bool_type(), nullptr, "and_tmp");
        ir_builder.CreateStore(child_l->get_llvm_value(), llvm_tmp);

        llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
        r_bb = llvm::BasicBlock::Create(llvm_context, "or_r", func);
        cont_bb = llvm::BasicBlock::Create(llvm_context, "or_cont", func);

        ir_builder.CreateCondBr(child_l->get_llvm_value(), cont_bb, r_bb);
        ir_builder.SetInsertPoint(r_bb);
    }
}

void ast_logic_or::codegen_r() {
    const sem_value &v = child_r->get_value();
    if (child_l->get_value().known) {
        if (v.known) {
            s_value = v;
            llvm_value = gen::get_llvm_bool(s_value);
        } else {
            llvm_value = child_r->get_llvm_value();
        }
    } else {
        ir_builder.CreateStore(child_r->get_llvm_value(), llvm_tmp);
        ir_builder.CreateBr(cont_bb);
        ir_builder.SetInsertPoint(cont_bb);
        llvm_value = ir_builder.CreateLoad(llvm_tmp, "load_or_tmp");
    }
}

void ast_logic_or::explain_impl(std::string &res, int indent) const {
    logic_explain_impl("or", res, indent);
}
