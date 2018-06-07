#include "gen/gen.h"
#include "ast/val/literal/ast_str_val.h"

ast_str_val::ast_str_val(char *str) {
    char *p_begin, *p_end;
    for (p_begin = str; *p_begin != 0; p_begin++) {
        if (*p_begin == '#') {
            p_begin++;
            auto t = (int) strtol(p_begin, &p_end, 10);
            if (p_begin == p_end) {
                this->str += '#';
            } else {
                this->str += (char) t;
            }
            p_begin = p_end - 1;
        } else {
            this->str += *p_begin;
        }
    }

    s_type = {false, type_group::STR, (int) this->str.size()};
    s_value = {true};
}

void ast_str_val::codegen() {
    llvm_mem = ir_builder.CreateGlobalString(str);
    llvm_value = ir_builder.CreateLoad(llvm_mem);
}

void ast_str_val::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "string(";
    for (auto &child : str) {
        if (child >= 32 && child <= 126) {
            res += child;
        } else {
            res += "\\" + std::to_string((int) child);
        }
    }
    res += ")\n";
}
