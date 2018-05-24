#include "ast/program/ast_block.h"

ast_block_head::~ast_block_head() {
    for (auto child : node_vec) {
        delete child;
    }
}

void ast_block_head::add_node(ast_node *node) {
    node_vec.emplace_back(node);
}

bool ast_block_head::analyse() {
    for (auto child : node_vec) {
        if (!child->analyse()) {
            return false;
        }
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

bool ast_block::analyse() {
    return head->analyse() && body->analyse();
}

void ast_block::explain_impl(std::string &res, int indent) const {
    head->explain_impl(res, indent);
    body->explain_impl(res, indent);
}
