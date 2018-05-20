#include "ast_id.h"
#include "env/env.h"

ast_id::ast_id(const char *id) : id(id) {}

type ast_id::value_type() {
    if (env_hash.find(id) == env_hash.end()) {
        return type::UNKNOWN;
    } else {
        return env_hash.at(id);
    }
}

bool ast_id::check() {
    return true;
}

void ast_id::explain_impl(std::string &res, int indent) {
    explain_indent(res, indent);
    res += "id(" + id + ")\n";
}
