#include "sem/exp/sem_arith.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_range_type.h"
#include "sem/type/sem_array_type.h"

std::vector<sem_array_type> array_type_vec;

bool sem_array_type::operator==(const sem_array_type &rhs) const {
    if (ele_type != rhs.ele_type) {
        return false;
    }
    if (size != rhs.size) {
        return false;
    }
    for (int i = 0; i < range_vec.size(); i++) {
        if (range_vec[i] != rhs.range_vec[i]) {
            return false;
        }
    }
    return true;
}

sem_array_type sem::make_array_type(const std::vector<ast_range_type *> &range_vec, ast_type_node *ele_type) {
    std::vector<int> v;
    for (auto &child : range_vec) {
        v.emplace_back(child->get_type().id);
    }
    sem_type s_ele_type = ele_type->get_type();

    // Element type may be another array type, so flatten that type.
    if (ele_type->get_type().tg == type_group::ARRAY) {
        const sem_array_type &a_t = sem::get_array_type_by_idx(ele_type->get_type().id);
        v.insert(v.end(), a_t.range_vec.begin(), a_t.range_vec.end());
        s_ele_type = a_t.ele_type;
    }

    return {s_ele_type, (int) v.size(), v};
}

int sem::get_or_define_array_type(const sem_array_type &type) {
    for (int i = 0; i < array_type_vec.size(); i++) {
        if (type == array_type_vec[i]) {
            return i;
        }
    }

    auto ret = (int) array_type_vec.size();
    array_type_vec.emplace_back(type);
    return ret;
}

const sem_array_type &sem::get_array_type_by_idx(int idx) {
    return array_type_vec[idx];
}

void sem::assert_is_array_value(const sem_type &type) {
    if (type.is_type || type.tg != type_group::ARRAY || type.ptr > 0) {
        throw sem_exception("semantics error, must be an array value");
    }
}
