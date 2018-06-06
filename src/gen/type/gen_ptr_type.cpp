#include "gen/type/gen_type.h"
#include "gen/type/gen_ptr_type.h"

llvm::PointerType *gen::get_ptr_type(const sem_type &type) {
    sem_type t = type;
    t.ptr--;
    return llvm::PointerType::getUnqual(get_llvm_type(t));
}
