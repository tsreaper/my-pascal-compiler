#include "ast/stmt/ast_stmt.h"

ast_stmt_seq::~ast_stmt_seq() {
    for (auto &child : stmt_vec) {
        delete child;
    }
}

void ast_stmt_seq::add_stmt(ast_node *stmt) {
    stmt_vec.emplace_back(stmt);
}

bool ast_stmt_seq::semantics_child() {
    for (auto &child : stmt_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_stmt_seq::explain_impl(std::string &res, int indent) const {
    for (auto &child : stmt_vec) {
        child->explain_impl(res, indent);
    }
}
