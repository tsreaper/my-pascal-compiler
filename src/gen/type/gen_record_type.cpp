#include "sem/type/sem_record_type.h"
#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/type/gen_record_type.h"

llvm::StructType *gen::get_llvm_record_type(const sem_type &type) {
    const sem_record_type &s_type = sem::get_record_type_by_idx(type.id);

    std::vector<llvm::Type *> llvm_type_vec;
    for (auto &t : s_type.type_vec) {
        llvm_type_vec.emplace_back(get_llvm_type(t));
    }
    return llvm::StructType::get(llvm_context, llvm_type_vec);
}
