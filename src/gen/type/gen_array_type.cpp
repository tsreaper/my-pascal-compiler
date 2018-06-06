#include "sem/type/sem_array_type.h"
#include "gen/type/gen_type.h"
#include "gen/type/gen_array_type.h"

llvm::ArrayType *gen::get_llvm_array_type(const sem_type &type) {
    const sem_array_type &s_type = sem::get_array_type_by_idx(type.id);

    llvm::ArrayType *array_type = nullptr;
    for (int i = s_type.size - 1; i >= 0; i--) {
        const sem_range_type &r_type = sem::get_range_type_by_idx(s_type.range_vec[i]);
        int len = sem::get_range_length(r_type);
        if (array_type == nullptr) {
            array_type = llvm::ArrayType::get(get_llvm_type(s_type.ele_type), (uint64_t) len);
        } else {
            array_type = llvm::ArrayType::get(array_type, (uint64_t) len);
        }
    }
    return array_type;
}
