#ifndef MPC_AST_RVAL_H
#define MPC_AST_RVAL_H

#include "ast/ast_node.h"

class ast_rval : public ast_value_node {
public:
    bool analyse(bool as_rval) override;
};

#define MUST_BE_RVAL { \
    try { \
        if (!as_rval) { \
            throw sem_exception("semantics error, expressions can not be left value"); \
        } \
    } catch (const sem_exception &e) { \
        PRINT_ERROR_MSG(e); \
        return false; \
    } \
}

#endif //MPC_AST_RVAL_H
