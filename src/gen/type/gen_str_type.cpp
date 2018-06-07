#include "gen/type/gen_builtin_type.h"
#include "gen/type/gen_str_type.h"

llvm::ArrayType *gen::get_llvm_str_type(const sem_type &type) {
    return llvm::ArrayType::get(get_llvm_char_type(), (uint64_t) type.id + 1);
}
