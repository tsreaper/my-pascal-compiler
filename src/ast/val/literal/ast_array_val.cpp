#include <llvm/IR/Constants.h>

#include "sem/type/sem_array_type.h"
#include "sem/exception/sem_exception.h"
#include "gen/type/gen_array_type.h"
#include "ast/val/literal/ast_array_val.h"

ast_array_val::ast_array_val(ast_exp_seq *value) : value(value) {
    s_type = {false};
    s_value = {true, {.num = -1}};
}

bool ast_array_val::semantics_child() {
    return value->analyse();
}

bool ast_array_val::semantics_self() {
    try {
        const sem_type &ele_type = (*value->get_exp_vec().begin())->get_type();
        for (auto &child : value->get_exp_vec()) {
            if (!child->get_value().known) {
                throw sem_exception("semantics error, array literal must have constant elements");
            }
            if (ele_type != child->get_type()) {
                throw sem_exception("semantics error, elements in the array must be of same type");
            }
        }

        s_type = {false, type_group::ARRAY, sem::get_or_define_array_type(sem::make_array_type_from_exp_seq(value))};
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_array_val::codegen() {
    std::vector<llvm::Constant *> vec;
    for (auto &child : value->get_exp_vec()) {
        vec.emplace_back((llvm::Constant *) child->get_llvm_value());
    }
    llvm_value = llvm::ConstantArray::get(gen::get_llvm_array_type(s_type), vec);
}

void ast_array_val::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "array(\n";
    value->explain_impl(res, indent + 1);
    explain_indent(res, indent);
    res += ")\n";
}
