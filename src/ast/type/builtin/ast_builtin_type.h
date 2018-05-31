#ifndef MPC_AST_BUILTIN_TYPE_H
#define MPC_AST_BUILTIN_TYPE_H

#include "ast/ast_node.h"
#include "sem/type/sem_type.h"

class ast_builtin_type : public ast_type_node {
public:
    const sem_type &get_type() const override;

protected:
    sem_type s_type = {false};
};



#endif //MPC_AST_BUILTIN_TYPE_H
