#include <stdexcept>

#include "gen/type/gen_builtin_type.h"
#include "gen/val/gen_literal.h"

llvm::Constant *gen::get_llvm_const(const sem_type &type, const sem_value &value) {
    switch (type.tg) {
        case type_group::BUILT_IN:
            switch (type.id) {
                case built_in_type::INT:
                    return get_llvm_int(value);
                case built_in_type::REAL:
                    return get_llvm_real(value);
                case built_in_type::CHAR:
                    return get_llvm_char(value);
                case built_in_type::BOOL:
                    return get_llvm_bool(value);
                default:
                    throw std::invalid_argument("[gen::get_llvm_const] Invalid built-in type");
            }
        case type_group::ENUM:
            return get_llvm_int(value);
        default:
            throw std::invalid_argument("[gen::get_llvm_const] Invalid type group");
    }
}

llvm::Constant *gen::get_llvm_int(const sem_value &value) {
    return llvm::ConstantInt::get(get_llvm_int_type(), (uint64_t) value.value.num, true);
}

llvm::Constant *gen::get_llvm_int(int value) {
    return llvm::ConstantInt::get(get_llvm_int_type(), (uint64_t) value, true);
}

llvm::Constant *gen::get_llvm_real(const sem_value &value) {
    return llvm::ConstantFP::get(get_llvm_real_type(), value.value.real);
}

llvm::Constant *gen::get_llvm_char(const sem_value &value) {
    return llvm::ConstantInt::get(get_llvm_char_type(), (uint64_t) value.value.chr, true);
}

llvm::Constant *gen::get_llvm_char(char value) {
    return llvm::ConstantInt::get(get_llvm_char_type(), (uint64_t) value, true);
}

llvm::Constant *gen::get_llvm_bool(const sem_value &value) {
    return llvm::ConstantInt::get(get_llvm_bool_type(), (uint64_t) value.value.boo, true);
}
