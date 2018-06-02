#include "ast/val/ast_lhs.h"

bool ast_lhs::analyse() {
    return analyse(true);
}

bool ast_lhs::analyse(bool as_rhs) {
    if (semantics_child() && semantics_self()) {
        if (as_rhs) {
            codegen();
        }
        return true;
    } else {
        return false;
    }
}
