#include "gen/gen.h"
#include "gen/exp/gen_arith.h"
#include "gen/type/gen_all_types.h"
#include "gen/func/sys/gen_sys_char_func.h"

llvm::Value *gen::gen_sys_chr(const std::vector<ast_value_node *> &args) {
    return ir_builder.CreateIntCast(args[0]->get_llvm_value(), get_llvm_char_type(), true, "i2c");
}

llvm::Value *gen::gen_sys_ord(const std::vector<ast_value_node *> &args) {
    return ir_builder.CreateIntCast(args[0]->get_llvm_value(), get_llvm_int_type(), true, "c2i");
}

llvm::Value *gen::gen_sys_succ(const std::vector<ast_value_node *> &args) {
    return gen_arith_add_one(built_in_type::CHAR_TYPE, args[0]->get_llvm_value());
}

llvm::Value *gen::gen_sys_pred(const std::vector<ast_value_node *> &args) {
    return gen_arith_sub_one(built_in_type::CHAR_TYPE, args[0]->get_llvm_value());
}
