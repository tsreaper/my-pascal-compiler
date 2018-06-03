#include "ast/exp/ast_exp_seq.h"

ast_exp_seq::~ast_exp_seq() {
    for (auto &child : exp_vec) {
        delete child;
    }
}

void ast_exp_seq::add_exp(ast_value_node *exp) {
    exp_vec.emplace_back(exp);
}

const std::vector<ast_value_node *> &ast_exp_seq::get_exp_vec() const {
    return exp_vec;
}

bool ast_exp_seq::semantics_child() {
    for (auto &child : exp_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

void ast_exp_seq::explain_impl(std::string &res, int indent) const {
    for (auto &child : exp_vec) {
        child->explain_impl(res, indent);
    }
}
