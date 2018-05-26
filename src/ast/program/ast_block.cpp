#include "ast/program/ast_block.h"

ast_block_head::~ast_block_head() {
    for (auto child : node_vec) {
        delete child;
    }
}

void ast_block_head::add_node(ast_node *node) {
    node_vec.emplace_back(node);
}

bool ast_block_head::semantics_child() {
    for (auto child : node_vec) {
        llvm::Value *code = child->analyse();
        if (code == nullptr) {
            return false;
        }
        code_node_vec.emplace_back(code);
    }
    return true;
}

void ast_block_head::explain_impl(std::string &res, int indent) const {
    for (auto child : node_vec) {
        child->explain_impl(res, indent);
    }
}

ast_block::ast_block(ast_block_head *head, ast_stmt_seq *body) : head(head), body(body) {}

ast_block::~ast_block() {
    delete head;
    delete body;
}

bool ast_block::semantics_child() {
    return (code_head = head->analyse()) != nullptr && (code_body = body->analyse()) != nullptr;
}

void ast_block::explain_impl(std::string &res, int indent) const {
    head->explain_impl(res, indent);
    body->explain_impl(res, indent);
}
