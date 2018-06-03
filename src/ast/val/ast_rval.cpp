#include "sem/exception/sem_exception.h"
#include "ast/val/ast_rval.h"

bool ast_rval::analyse(bool as_rval) {
    MUST_BE_RVAL;

    return ast_value_node::analyse(as_rval);
}
