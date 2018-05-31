#ifndef MPC_AST_LOOP_H
#define MPC_AST_LOOP_H

#include "ast/ast_node.h"

class ast_loop : public ast_node {
public:
    virtual llvm::BasicBlock *get_continue_block() const = 0;

    virtual llvm::BasicBlock *get_break_block() const = 0;
};

#endif //MPC_AST_LOOP_H
