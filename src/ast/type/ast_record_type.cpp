#include <set>

#include "sem/type/sem_record_type.h"
#include "sem/exception/sem_exception.h"
#include "ast/type/ast_record_type.h"

ast_record_type::~ast_record_type() {
    for (auto &child : seq_vec) {
        delete child;
    }
}

void ast_record_type::add_seq(ast_id_seq_with_type *seq) {
    seq_vec.emplace_back(seq);
}

bool ast_record_type::semantics_child() {
    for (auto &child : seq_vec) {
        if (!child->analyse()) {
            return false;
        }
    }
    return true;
}

bool ast_record_type::semantics_self() {
    try {
        // Init id and type vector
        for (auto &seq : seq_vec) {
            for (auto &child : seq->get_id_vec()) {
                id_vec.emplace_back(child);
            }
            for (int i = 0; i < seq->get_id_vec().size(); i++) {
                type_vec.emplace_back(seq->get_type());
            }
        }

        std::set<std::string> id_set;
        for (auto &child : id_vec) {
            const std::string &id = child->get_id();
            if (id_set.find(id) != id_set.end()) {
                throw sem_exception("semantics error, duplicated member name " + id);
            }
            id_set.insert(id);
        }

        sem_record_type record_type = sem::make_record_type(id_vec, type_vec);
        record_id = sem::define_record_type(record_type);
        s_type = {true, type_group::RECORD, record_id};
        return true;
    } catch (const sem_exception &e) {
        PRINT_ERROR_MSG(e);
        return false;
    }
}

void ast_record_type::explain_impl(std::string &res, int indent) const {
    explain_indent(res, indent);
    res += "record_type(\n";
    for (auto &child : seq_vec) {
        child->explain_impl(res, indent + 1);
    }
    explain_indent(res, indent);
    res += ")\n";
}
