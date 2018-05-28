#include <stdexcept>

#include "gen/gen.h"
#include "gen/type/gen_type.h"

llvm::Type *gen::get_llvm_type(const sem_type &type) {
    switch (type.tg) {
        case type_group::BUILT_IN:
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
        case type_group::ENUM:
            return get_llvm_int_type();
        default:
            throw std::invalid_argument("[gen::get_llvm_type] Invalid type group");
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

void gen::to_llvm_arith_type(
        const sem_type &type_l, const sem_type &type_r, llvm::Value **value_l, llvm::Value **value_r
) {
    if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::INT_TYPE) {
        return;
    } else if (type_l == built_in_type::INT_TYPE && type_r == built_in_type::REAL_TYPE) {
        *value_l = ir_builder.CreateSIToFP(*value_l, get_llvm_real_type(), "i2r_tmp");
    } else if (type_l == built_in_type::REAL_TYPE && type_r == built_in_type::INT_TYPE) {
        *value_r = ir_builder.CreateSIToFP(*value_r, get_llvm_real_type(), "i2r_tmp");
    } else if (type_l != built_in_type::REAL_TYPE && type_r != built_in_type::REAL_TYPE) {
        throw std::invalid_argument("[gen::to_llvm_arith_type] Invalid arithmetic type");
    }
}

void gen::to_llvm_real_type(const sem_type &type, llvm::Value **value) {
    if (type == built_in_type::INT_TYPE) {
        *value = ir_builder.CreateSIToFP(*value, get_llvm_real_type(), "i2r_tmp");
    } else if (type != built_in_type::REAL_TYPE) {
        throw std::invalid_argument("[gen::to_llvm_real_type] Cannot case this type to real");
    }
}
