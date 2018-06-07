#include "sem/sem.h"
#include "sem/func/sem_func.h"
#include "sem/stmt/sem_assign.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/func/gen_exit.h"
#include "gen/type/gen_convert.h"
#include "ast/func/ast_exit.h"

ast_exit::ast_exit(ast_value_node *ret_val) : ret_val(ret_val) {}

bool ast_exit::semantics_child() {
    return ret_val == nullptr || ret_val->analyse();
}

bool ast_exit::semantics_self() {
    if (ret_val == nullptr) {
        return true;
    }

    try {
        if (sem_env.is_global()) {
            ret_type = built_in_type::INT_TYPE;
        } else {
            const func_sign &sign = sem::get_current_func_sign();
            ret_type = sem::get_ret_type(sign);
        }

        if (!sem::can_assign(ret_type, ret_val->get_type())) {
            throw sem_exception("semantics error, return value type is not consistent with the procedure/function");
        }
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_exit::codegen() {
    if (ret_val != nullptr) {
        gen::gen_exit(gen::llvm_type_convert(ret_type, ret_val));
    } else {
        // No return value specified. Use default value
        gen::gen_exit();
    }
    llvm::Function *func = ir_builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(llvm_context, "exit_cont", func);
    ir_builder.SetInsertPoint(bb);
}

void ast_exit::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "exit()\n";
}
