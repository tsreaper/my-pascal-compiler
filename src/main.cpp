#include <iostream>
#include <string>

#include "ast/ast.h"
#include "pascal.y.hpp"

int main() {
    if (yyparse() == 0) {
        std::string plan;
        ast_root->explain(plan);
        std::cout << plan << std::endl;
    }
    return 0;
}