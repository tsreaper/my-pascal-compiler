#include <iostream>
#include <string>

#include "ast/ast.h"
#include "pascal.y.hpp"

int main() {
    if (yyparse() == 0) {
        std::string plan;
        ast_root->explain(plan);
        std::cout << plan << std::endl;
        if (ast_root->analyse() != nullptr) {
            std::cout << "OK" << std::endl;
        }
    }
    return 0;
}
