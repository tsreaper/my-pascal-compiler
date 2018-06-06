#include "sem/type/sem_type.h"
#include "sem/exp/sem_cmp.h"
#include "sem/exception/sem_exception.h"
#include "gen/exp/gen_cmp.h"
#include "ast/exp/cmp/ast_cmp.h"

ast_cmp::ast_cmp(ast_value_node *child_l, ast_value_node *child_r) : ast_binop(child_l, child_r) {
    s_type = built_in_type::BOOL_VAL;
}

bool ast_cmp::cmp_semantics_impl(bool need_eq, bool need_cmp) {
    try {
        if (need_eq) {
            s_type = sem::assert_can_equal(conv_type_l, conv_type_r);
        }
        if (need_cmp) {
            s_type = sem::assert_can_compare(conv_type_l, conv_type_r);
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}
