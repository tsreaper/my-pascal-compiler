#include "gen/gen.h"
#include "gen/func/sys/gen_all_sys_funcs.h"
#include "gen/val/gen_literal.h"
#include "gen/type/gen_all_types.h"
#include "gen/type/gen_convert.h"

llvm::Value *gen::llvm_type_convert(const sem_type &dest_t, ast_value_node *node) {
    const sem_type &src_t = node->get_type();
    llvm::Value *value = node->get_llvm_value();
    if (src_t == dest_t) {
        return value;
    }

    if (src_t == built_in_type::INT_TYPE && dest_t == built_in_type::REAL_TYPE) {
        return ir_builder.CreateSIToFP(value, get_llvm_real_type());
    } else if (src_t == built_in_type::CHAR_TYPE && dest_t.tg == type_group::STR) {
        llvm::Value *mem = gen_char_to_str_mem(value);
        return gen_sys_copy_impl(mem, get_llvm_int(1), get_llvm_int(dest_t.id), dest_t.id);
    } else if (src_t.tg == type_group::STR && dest_t.tg == type_group::STR) {
        if (dest_t.id != INT_MAX) {
            return gen_sys_copy_impl(
                    node->get_llvm_mem(), get_llvm_int(1), get_llvm_int(dest_t.id), dest_t.id
            );
        }
    }

    return value;
}
