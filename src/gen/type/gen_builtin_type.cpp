#include <stdexcept>

#include "gen/gen.h"
#include "gen/type/gen_builtin_type.h"

llvm::Type *gen::get_llvm_builtin_type(const sem_type &type) {
    switch (type.id) {
        case built_in_type::INT:
            return get_llvm_int_type();
        case built_in_type::REAL:
            return get_llvm_real_type();
        case built_in_type::CHAR:
            return get_llvm_char_type();
        case built_in_type::BOOL:
            return get_llvm_bool_type();
        case built_in_type::VOID:
            return get_llvm_void_type();
        default:
            throw std::invalid_argument("[gen::get_llvm_type] Invalid built-in type");
    }
}

llvm::Type *gen::get_llvm_int_type() {
    return llvm::Type::getInt32Ty(llvm_context);
}

llvm::Type *gen::get_llvm_real_type() {
    return llvm::Type::getDoubleTy(llvm_context);
}

llvm::Type *gen::get_llvm_char_type() {
    return llvm::Type::getInt8Ty(llvm_context);
}

llvm::Type *gen::get_llvm_bool_type() {
    return llvm::Type::getInt1Ty(llvm_context);
}

llvm::Type *gen::get_llvm_void_type() {
    return llvm::Type::getVoidTy(llvm_context);
}
