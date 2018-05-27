#include <iostream>
#include <string>

#include <llvm/Support/Error.h>

#include "ast/ast.h"
#include "gen/gen.h"
#include "pascal.y.hpp"

int main() {
    if (yyparse() == 0) {
        std::string plan;
        ast_root->explain(plan);
        std::cout << plan << std::endl;

        if (ast_root->analyse()) {
            std::cout << "OK" << std::endl;
            llvm_module.print(llvm::errs(), nullptr);
        }
    }
    return 0;
}
