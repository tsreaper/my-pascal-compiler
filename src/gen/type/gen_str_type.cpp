#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "gen/exp/gen_logic.h"
#include "gen/func/sys/gen_sys_concat.h"
#include "gen/func/sys/gen_sys_strcmp.h"
#include "gen/type/gen_builtin_type.h"
#include "gen/type/gen_str_type.h"

llvm::ArrayType *gen::get_llvm_str_type(const sem_type &type) {
    return llvm::ArrayType::get(get_llvm_char_type(), (uint64_t) type.id + 1);
}

llvm::Value *gen::gen_str_add(ast_value_node *node_l, ast_value_node *node_r) {
    return gen_sys_concat_impl(
            {node_l->get_llvm_mem(), node_r->get_llvm_mem()},
            node_l->get_type().id + node_r->get_type().id
    );
}

llvm::Value *gen::gen_str_eq(ast_value_node *node_l, ast_value_node *node_r) {
    return ir_builder.CreateICmpEQ(
            gen_sys_strcmp_impl(node_l->get_llvm_mem(), node_r->get_llvm_mem()),
            get_llvm_int(0),
            "str_eq_tmp"
    );
}

llvm::Value *gen::gen_str_ne(ast_value_node *node_l, ast_value_node *node_r) {
    return gen_logic_not(gen_str_eq(node_l, node_r));
}

llvm::Value *gen::gen_str_lt(ast_value_node *node_l, ast_value_node *node_r) {
    return ir_builder.CreateICmpSLT(
            gen_sys_strcmp_impl(node_l->get_llvm_mem(), node_r->get_llvm_mem()),
            get_llvm_int(0),
            "str_lt_tmp"
    );
}

llvm::Value *gen::gen_str_gt(ast_value_node *node_l, ast_value_node *node_r) {
    return gen_str_lt(node_r, node_l);
}

llvm::Value *gen::gen_str_le(ast_value_node *node_l, ast_value_node *node_r) {
    return gen_logic_or(gen_str_lt(node_l, node_r), gen_str_eq(node_l, node_r));
}

llvm::Value *gen::gen_str_ge(ast_value_node *node_l, ast_value_node *node_r) {
    return gen_logic_or(gen_str_gt(node_l, node_r), gen_str_eq(node_l, node_r));
}
