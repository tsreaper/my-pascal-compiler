#include "sem/val/sem_value.h"
#include "sem/exp/sem_cmp.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/exp/gen_cmp.h"
#include "gen/exp/gen_logic.h"
#include "ast/stmt/cond/ast_case.h"

ast_case::ast_case(ast_value_node *lhs) : lhs(lhs) {}

ast_case::~ast_case() {
    delete lhs;
    for (auto &child : seq_vec) {
        delete child;
    }
    for (auto &child : body_vec) {
        delete child;
    }
    delete default_body;
}

void ast_case::add_seq(ast_exp_seq *seq, ast_node *body) {
    seq_vec.emplace_back(seq);
    body_vec.emplace_back(body);
}

void ast_case::set_default(ast_node *body) {
    default_body = body;
}

bool ast_case::analyse() {
    codegen_before();

    if (!semantics_lhs()) {
        return false;
    }

    for (int i = 0; i < seq_vec.size(); i++) {
        llvm::BasicBlock *nxt_block = (i < seq_vec.size() - 1 ? seq_block_vec[i + 1] : default_block);

        if (!semantics_seq(seq_vec[i])) {
            return false;
        }
        codegen_seq(seq_vec[i], body_block_vec[i], nxt_block);

        if (!semantics_body(body_vec[i])) {
            return false;
        }
        codegen_body(nxt_block);
    }

    if (!semantics_default()) {
        return false;
    }
    codegen_default();

    return true;
}

void ast_case::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "case(\n";

    explain_indent(res, indent + 1);
    res += "--- lhs ---\n";
    lhs->explain_impl(res, indent + 1);

    for (int i = 0; i < seq_vec.size(); i++) {
        explain_indent(res, indent + 1);
        res += "--- cond ---\n";
        seq_vec[i]->explain_impl(res, indent + 1);
        explain_indent(res, indent + 1);
        res += "--- body ---\n";
        body_vec[i]->explain_impl(res, indent + 1);
    }

    if (default_body != nullptr) {
        explain_indent(res, indent + 1);
        res += "--- default ---\n";
        default_body->explain_impl(res, indent + 1);
    }

    explain_indent(res, indent);
    res += ")\n";
}

bool ast_case::semantics_lhs() {
    return lhs->analyse();
}

bool ast_case::semantics_seq(ast_exp_seq *seq) {
    if (!seq->analyse()) {
        return false;
    }
    try {
        if (seq->get_exp_vec().empty()) {
            throw sem_exception("semantics error, expression list must not be empty");
        }
        for (auto &exp : seq->get_exp_vec()) {
            sem::assert_can_equal(lhs->get_type(), exp->get_type());
        }
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
    return true;
}

bool ast_case::semantics_body(ast_node *body) {
    return body->analyse();
}

bool ast_case::semantics_default() {
    return default_body == nullptr || default_body->analyse();
}

void ast_case::codegen_before() {
    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    for (int i = 0; i < seq_vec.size(); i++) {
        seq_block_vec.emplace_back(llvm::BasicBlock::Create(llvm_context, "case_branch", func));
        body_block_vec.emplace_back(llvm::BasicBlock::Create(llvm_context, "case_body", func));
    }
    default_block = llvm::BasicBlock::Create(llvm_context, "case_default", func);
    cont_block = llvm::BasicBlock::Create(llvm_context, "case_cont", func);

    llvm::BasicBlock *bb = seq_block_vec.empty() ? default_block : *seq_block_vec.begin();
    ir_builder.CreateBr(bb);
    ir_builder.SetInsertPoint(bb);
}

void ast_case::codegen_seq(ast_exp_seq *seq, llvm::BasicBlock *body_block, llvm::BasicBlock *nxt_block) {
    llvm::Value *llvm_cond = nullptr;
    for (auto &child : seq->get_exp_vec()) {
        llvm::Value *v = gen::gen_cmp_eq(
                lhs->get_type(), child->get_type(), lhs->get_llvm_value(), child->get_llvm_value()
        );
        if (llvm_cond == nullptr) {
            llvm_cond = v;
        } else {
            llvm_cond = gen::gen_logic_or(llvm_cond, v);
        }
    }

    ir_builder.CreateCondBr(llvm_cond, body_block, nxt_block);
    ir_builder.SetInsertPoint(body_block);
}

void ast_case::codegen_body(llvm::BasicBlock *nxt_block) {
    ir_builder.CreateBr(cont_block);
    ir_builder.SetInsertPoint(nxt_block);
}

void ast_case::codegen_default() {
    ir_builder.CreateBr(cont_block);
    ir_builder.SetInsertPoint(cont_block);
}
