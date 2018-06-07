#include "sem/sem.h"
#include "sem/stmt/sem_assign.h"
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

bool func_sign::can_be_called(const func_sign &call_inst_sign) const {
    if (id != call_inst_sign.id) {
        return false;
    }
    if (param_type_vec.size() != call_inst_sign.param_type_vec.size()) {
        return false;
    }
    for (int i = 0; i < param_type_vec.size(); i++) {
        if (!sem::can_assign(param_type_vec[i], call_inst_sign.param_type_vec[i])) {
            return false;
        }
    }
    return true;
}

void sem_func_context::push(const func_sign &current_sign) {
    type_layers.emplace_back();
    defined_layers.emplace_back();
    current_func_sign.emplace_back(current_sign);
}

void sem_func_context::pop() {
    type_layers.pop_back();
    defined_layers.pop_back();
    current_func_sign.pop_back();
}

const func_sign &sem_func_context::get_current_func_sign() const {
    return *current_func_sign.rbegin();
}

#define FIND_SIGNATURE(sign, layer, res) { \
    for (int i = 0; i < (layer).size(); i++) { \
        if ((sign) == (layer)[i].first) { \
            (res) = i; \
            break; \
        } \
    } \
}

const func_sign_ret &sem_func_context::get_func_sign_ret(const func_sign &sign) const {
    for (auto it = type_layers.rbegin(); it != type_layers.rend(); it++) {
        int pos = -1;
        FIND_SIGNATURE(sign, *it, pos);
        if (pos >= 0) {
            return (*it)[pos];
        }
    }
    throw sem_exception("semantics error, undeclared procedure/function " + sign.id);
}

#define FIND_CALL_SIGNATURE(sign, layer, res) { \
    for (int i = 0; i < (layer).size(); i++) { \
        if ((layer)[i].first.can_be_called(sign)) { \
            (res) = i; \
            break; \
        } \
    } \
}

const func_sign_ret &sem_func_context::get_call_func_sign_ret(const func_sign &call_sign) const {
    for (auto it = type_layers.rbegin(); it != type_layers.rend(); it++) {
        int pos = -1;
        FIND_CALL_SIGNATURE(call_sign, *it, pos);
        if (pos >= 0) {
            return (*it)[pos];
        }
    }
    throw sem_exception("semantics error, undeclared procedure/function " + call_sign.id);
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

void sem::declare_func(const func_sign& sign, const sem_type &ret_type) {
    sem_env.get_func_env().set_ret_type(sign, ret_type);
}

void sem::define_func(const func_sign &sign, const sem_type &ret_type) {
    try {
        declare_func(sign, ret_type);
    } catch (const sem_exception &e) {}

    if (sem_env.get_func_env().get_func_sign_ret(sign).second != ret_type) {
        throw sem_exception("semantics error, duplicated procedure/function " + sign.id);
    }

    sem_env.get_func_env().set_defined(sign);
}

const sem_type &sem::get_ret_type(const func_sign &sign) {
    return sem_env.get_func_env().get_func_sign_ret(sign).second;
}

const func_sign &sem::get_current_func_sign() {
    return sem_env.get_func_env().get_current_func_sign();
}
