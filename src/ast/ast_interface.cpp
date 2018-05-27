#include "ast/ast_interface.h"

llvm::Value *ast_has_value::get_llvm_value() const {
    return llvm_value;
}
