#include "gen/gen.h"
#include "gen/type/gen_type.h"
#include "gen/val/gen_literal.h"
#include "ast/type/ast_size_of.h"

ast_size_of::ast_size_of(ast_type_node *type) : type(type) {
    s_type = built_in_type::INT_VAL;
    s_value = {false};
}

ast_size_of::~ast_size_of() {
    delete type;
}

bool ast_size_of::semantics_child() {
    return type->analyse();
}

void ast_size_of::codegen() {
    auto size = (int) llvm_data.getTypeAllocSize(gen::get_llvm_type(type->get_type()));
    s_value = {true, {.num = size}};
    llvm_value = gen::get_llvm_int(size);
}

void ast_size_of::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "size_of(\n";
    type->explain_impl(res, indent);
    explain_indent(res, indent);
    res += ")\n";
}
