#include "ast/id/ast_id_seq.h"

ast_id_seq::~ast_id_seq() {
    for (auto &child : id_vec) {
        delete child;
    }
}

void ast_id_seq::add_id(ast_id *id) {
    id_vec.emplace_back(id);
}

const std::vector<ast_id *> &ast_id_seq::get_id_vec() const {
    return id_vec;
}

bool ast_id_seq::semantics_child() {
    for (auto &child : id_vec) {
        if (!child->analyse(false)) {
            return false;
        }
    }
    return true;
}

void ast_id_seq::explain_impl(std::string &res, int indent) const {
    for (auto &child : id_vec) {
        child->explain_impl(res, indent);
    }
}
