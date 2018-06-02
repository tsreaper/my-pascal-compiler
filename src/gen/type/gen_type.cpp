#include <stdexcept>

#include "sem/type/sem_range_type.h"
#include "sem/type/sem_array_type.h"
#include "gen/gen.h"
#include "gen/type/gen_type.h"

llvm::Type *gen::get_llvm_type(const sem_type &type) {
    if (type.ptr > 0) {
        sem_type t = type;
        t.ptr--;
        return llvm::PointerType::getUnqual(get_llvm_type(t));
    }

    switch (type.tg) {
        case type_group::BUILT_IN:
            return get_builtin_type(type);
        case type_group::ENUM:
            return get_llvm_int_type();
        case type_group::ARRAY:
            return get_llvm_array_type(type);
        default:
            throw std::invalid_argument("[gen::get_llvm_type] Invalid type group");
    }
}

llvm::Type *gen::get_builtin_type(const sem_type &type) {
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

llvm::Type *gen::get_llvm_array_type(const sem_type &type) {
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
