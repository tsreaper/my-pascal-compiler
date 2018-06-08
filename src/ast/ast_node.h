#ifndef MPC_AST_NODE_H
#define MPC_AST_NODE_H

#include <string>

#include <llvm/IR/Value.h>

#include "sem/type/sem_type.h"
#include "sem/val/sem_value.h"

#define PRINT_ERROR_MSG(e) fprintf(stderr, "%s (at %d:%d)\n", (e).what(), lineno, colno)

class ast_node {
public:
    virtual ~ast_node() = default;

    void set_location(int lineno, int colno);

    virtual bool analyse();

    void explain(std::string &res) const;

    virtual void explain_impl(std::string &res, int indent) const = 0;

protected:
    int lineno, colno;

    virtual bool semantics_child();

    virtual bool semantics_self();

    virtual void codegen();

    void explain_indent(std::string &res, int indent) const;
};

class ast_type_node : public ast_node {
public:
    virtual const sem_type &get_type() const;

protected:
    sem_type s_type = {false};
};

class ast_value_node : public ast_type_node {
public:
    virtual const sem_value &get_value() const;

    llvm::Value *get_llvm_value() const;

    virtual llvm::Value *get_llvm_mem() const;

    virtual bool is_rval() const;

    bool analyse() override;

    virtual bool analyse(bool as_rval);

protected:
    sem_value s_value = {false};

    llvm::Value *llvm_value = nullptr;
    llvm::Value *llvm_mem = nullptr;
};

#endif //MPC_AST_NODE_H
