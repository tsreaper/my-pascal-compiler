#include "ast/val/literal/ast_literal.h"

const sem_type &ast_literal::get_type() const {
    return s_type;
}

const sem_value &ast_literal::get_value() const {
    return s_value;
}
