#include "sem/type/sem_record_type.h"
#include "sem/exception/sem_exception.h"
#include "gen/gen.h"
#include "gen/val/gen_literal.h"
#include "ast/exp/record/ast_field.h"

ast_field::ast_field(ast_value_node *record, const std::string &name) : record(record), name(name) {}

ast_field::~ast_field() {
    delete record;
}

bool ast_field::semantics_child() {
    return record->analyse(false);
}

bool ast_field::semantics_self() {
    try {
        const sem_type &t = record->get_type();
        sem::assert_is_record_value(t);

        const sem_record_type &old_rec_t = sem::get_record_type_by_idx(record->get_type().id);
        int bias = sem::get_bias_in_record(old_rec_t, name);
        if (bias < 0) {
            throw sem_exception("semantics error, " + name + " is not a field in this record");
        }

        s_type = old_rec_t.type_vec[bias];

        std::vector<llvm::Value *> gep_vec = {
                gen::get_llvm_int(sem_value{true, {.num = 0}}),
                gen::get_llvm_int(sem_value{true, {.num = bias}})
        };
        llvm_mem = ir_builder.CreateGEP(record->get_llvm_mem(), gep_vec, "record_field");
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_field::codegen() {
    llvm_value = ir_builder.CreateLoad(llvm_mem, "load_record_field");
}

void ast_field::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "record_field(\n";

    record->explain_impl(res, indent + 1);
    explain_indent(res, indent + 1);
    res += "--- field ---\n";
    explain_indent(res, indent + 1);
    res += name + "\n";

    explain_indent(res, indent);
    res += ")\n";
}
