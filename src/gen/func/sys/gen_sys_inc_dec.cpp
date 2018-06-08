#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/exp/gen_arith.h"
#include "gen/func/sys/gen_sys_inc_dec.h"

llvm::Value *gen::gen_sys_inc(const std::vector<ast_value_node *> &args) {
    llvm::Value *llvm_res = nullptr;
    if (args.size() == 1) {
        llvm_res = gen_arith_add_one(args[0]->get_type(), args[0]->get_llvm_value());
    } else {
        llvm::Value *r_val = ir_builder.CreateIntCast(
                args[1]->get_llvm_value(), get_llvm_type(args[0]->get_type()), true
        );
        llvm_res = gen_arith_add(args[0]->get_type(), args[0]->get_llvm_value(), r_val);
    }
    return ir_builder.CreateStore(llvm_res, args[0]->get_llvm_mem());
}

llvm::Value *gen::gen_sys_dec(const std::vector<ast_value_node *> &args) {
    llvm::Value *llvm_res = nullptr;
    if (args.size() == 1) {
        llvm_res = gen_arith_sub_one(args[0]->get_type(), args[0]->get_llvm_value());
    } else {
        llvm::Value *r_val = ir_builder.CreateIntCast(
                args[1]->get_llvm_value(), get_llvm_type(args[0]->get_type()), true
        );
        llvm_res = gen_arith_sub(args[0]->get_type(), args[0]->get_llvm_value(), r_val);
    }
    return ir_builder.CreateStore(llvm_res, args[0]->get_llvm_mem());
}
