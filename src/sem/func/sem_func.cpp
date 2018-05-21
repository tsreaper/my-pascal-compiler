#include "sem/sem.h"
#include "sem/exception/sem_exception.h"
#include "sem/func/sem_func.h"

bool func_sign::operator==(const func_sign &rhs) const {
    if (id != rhs.id) {
        return false;
    }
    if (param_type_vec.size() != rhs.param_type_vec.size()) {
        return false;
    }
    for (int i = 0; i < param_type_vec.size(); i++) {
        if (param_type_vec[i] != rhs.param_type_vec[i]) {
            return false;
        }
    }
    return true;
}

bool func_sign::operator!=(const func_sign &rhs) const {
    return !(*this == rhs);
}

void sem_func_context::push() {
    layers.emplace_back();
}

void sem_func_context::pop() {
    layers.pop_back();
}

const sem_type &sem_func_context::get_ret_type(const func_sign &sign) const {
    for (auto it = layers.rbegin(); it != layers.rend(); it++) {
        int pos = find_signature(sign, *it);
        if (pos >= 0) {
            return (*it)[pos].second;
        }
    }
    throw sem_exception("semantics error, unknown procedure/function " + sign.id);
}

void sem_func_context::set_ret_type(const func_sign &sign, const sem_type &ret_type) {
    auto &layer = *layers.rbegin();
    int pos = find_signature(sign, layer);
    if (pos >= 0) {
        throw sem_exception("semantics error, duplicated procedure/function " + sign.id);
    }
    layer.emplace_back(func_sign_ret{sign, ret_type});
}

int sem_func_context::find_signature(const func_sign &sign, const std::vector<func_sign_ret> &layer) const {
    for (int i = 0; i < layer.size(); i++) {
        if (sign == layer[i].first) {
            return i;
        }
    }
    return -1;
}

void declare_func(const std::string &id, const std::vector<ast_type_node*> &param_type_vec, const sem_type &ret_type) {
    std::vector<sem_type> vec;
    for (auto child : param_type_vec) {
        vec.emplace_back(child->get_type());
    }
    func_sign sign{id, vec};
    sem_env.get_func_env().set_ret_type(sign, ret_type);
}
