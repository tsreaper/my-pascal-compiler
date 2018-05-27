#include "ast/type/builtin/ast_builtin_type.h"

const sem_type &ast_builtin_type::get_type() const {
    return s_type;
}
