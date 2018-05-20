#ifndef MY_PASCAL_AST_LABEL_H
#define MY_PASCAL_AST_LABEL_H

#include "ast_node.h"

class ast_label_dec_part : public ast_node {
public:
    ast_label_dec_part(int label, ast_node *next_dec);

    ~ast_label_dec_part() override;

    bool check() override;

    void explain_impl(std::string &res, int indent) override;

private:
    int label;
    ast_node *next_dec;
};

#endif //MY_PASCAL_AST_LABEL_H
