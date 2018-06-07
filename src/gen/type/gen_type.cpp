#include <stdexcept>

#include "sem/type/sem_range_type.h"
#include "sem/type/sem_array_type.h"
#include "sem/type/sem_record_type.h"
#include "gen/type/gen_builtin_type.h"
#include "gen/type/gen_ptr_type.h"
#include "gen/type/gen_array_type.h"
#include "gen/type/gen_str_type.h"
#include "gen/type/gen_record_type.h"
#include "gen/type/gen_type.h"

llvm::Type *gen::get_llvm_type(const sem_type &type) {
    if (type.ptr > 0) {
        return get_llvm_ptr_type(type);
    }

    switch (type.tg) {
        case type_group::BUILT_IN:
            return get_llvm_builtin_type(type);
        case type_group::ENUM:
            return get_llvm_int_type();
        case type_group::ARRAY:
            return get_llvm_array_type(type);
        case type_group::STR:
            return get_llvm_str_type(type);
        case type_group::RECORD:
            return get_llvm_record_type(type);
        default:
            throw std::invalid_argument("[gen::get_llvm_type] Invalid type group");
    }
}
