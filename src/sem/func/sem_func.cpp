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
    type_layers.emplace_back();
    defined_layers.emplace_back();
}

void sem_func_context::pop() {
    type_layers.pop_back();
    defined_layers.pop_back();
}

#define FIND_SIGNATURE(sign, layer, res) { \
    for (int i = 0; i < (layer).size(); i++) { \
        if ((sign) == (layer)[i].first) { \
            (res) = i; \
            break; \
        } \
    } \
}

const sem_type &sem_func_context::get_ret_type(const func_sign &sign) const {
    for (auto it = type_layers.rbegin(); it != type_layers.rend(); it++) {
        int pos = -1;
        FIND_SIGNATURE(sign, *it, pos);
        if (pos >= 0) {
            return (*it)[pos].second;
        }
    }
    throw sem_exception("semantics error, unknown procedure/function " + sign.id);
}

void sem_func_context::set_ret_type(const func_sign &sign, const sem_type &ret_type) {
    auto &layer = *type_layers.rbegin();
    int pos = -1;
    FIND_SIGNATURE(sign, layer, pos);
    if (pos >= 0) {
        throw sem_exception("semantics error, duplicated procedure/function " + sign.id);
    }
    layer.emplace_back(func_sign_ret{sign, ret_type});
}

void sem_func_context::set_defined(const func_sign &sign) {
    auto &layer = *defined_layers.rbegin();
    int pos = -1;
    FIND_SIGNATURE(sign, layer, pos);
    if (pos >= 0) {
        throw sem_exception("semantics error, procedure/function " + sign.id + " already defined");
    }
    layer.emplace_back(func_sign_defined{sign, true});
}

void declare_func(const func_sign& sign, const sem_type &ret_type) {
    sem_env.get_func_env().set_ret_type(sign, ret_type);
}

void define_func(const func_sign &sign, const sem_type &ret_type) {
    try {
        declare_func(sign, ret_type);
    } catch (const sem_exception &e) {}

    if (sem_env.get_func_env().get_ret_type(sign) != ret_type) {
        throw sem_exception("semantics error, duplicated procedure/function " + sign.id);
    }

    sem_env.get_func_env().set_defined(sign);
}
