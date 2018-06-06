#include "gen/gen.h"
#include "gen/type/gen_builtin_type.h"
#include "gen/type/gen_convert.h"

llvm::Value *gen::llvm_type_convert(const sem_type &src_t, const sem_type &dest_t, llvm::Value *value) {
    if (src_t == built_in_type::INT_TYPE && dest_t == built_in_type::REAL_TYPE) {
        return ir_builder.CreateSIToFP(value, get_llvm_real_type());
    }
    return value;
}
