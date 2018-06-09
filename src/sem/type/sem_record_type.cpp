#include <set>

#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_record_type.h"

void sem_record_context::push() {
    record_count.emplace_back();
    if (record_count.size() > 1) {
        *record_count.rbegin() = *prev(record_count.rbegin());
    }
}

void sem_record_context::pop() {
    record_count.pop_back();
    if (!record_count.empty()) {
        record_table.resize((unsigned long) *record_count.rbegin());
    } else {
        record_table.clear();
    }
}

const sem_record_type &sem_record_context::get_record_type(int idx) const {
    return record_table[idx];
}

int sem_record_context::add_record_type(const sem_record_type &type) {
    auto record_id = (int) record_table.size();
    record_table.emplace_back(type);
    *record_count.rbegin() += 1;
    return record_id;
}

sem_record_type sem::make_record_type(const std::vector<ast_id *> &id_vec, const std::vector<sem_type> &type_vec) {
    // Check duplicate member
    std::set<std::string> id_set;
    for (auto &child : id_vec) {
        const std::string &id = child->get_id();
        if (id_set.find(id) != id_set.end()) {
            throw sem_exception("semantics error, duplicated member name " + id);
        }
        id_set.insert(id);
    }

    // Make record type
    sem_record_type ret;
    ret.size = (int) id_vec.size();
    for (auto &child : id_vec) {
        ret.id_vec.emplace_back(child->get_id());
    }
    for (auto &child : type_vec) {
        ret.type_vec.emplace_back(child);
        (*ret.type_vec.rbegin()).is_type = false;
    }
    return ret;
}

int sem::define_record_type(const sem_record_type &type) {
    return sem_env.get_record_env().add_record_type(type);
}

const sem_record_type &sem::get_record_type_by_idx(int idx) {
    return sem_env.get_record_env().get_record_type(idx);
}

void sem::assert_is_record_value(const sem_type &type) {
    if (type.is_type || type.tg != type_group::RECORD || type.ptr > 0) {
        throw sem_exception("semantics error, must be a record value on the left");
    }
}

int sem::get_bias_in_record(const sem_record_type &type, const std::string &name) {
    for (int i = 0; i < type.size; i++) {
        if (type.id_vec[i] == name) {
            return i;
        }
    }
    return -1;
}
