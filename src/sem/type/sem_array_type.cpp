#include "sem/exp/sem_arith.h"
#include "sem/stmt/sem_assign.h"
#include "sem/exception/sem_exception.h"
#include "sem/type/sem_range_type.h"
#include "sem/type/sem_array_type.h"

std::vector<sem_array_type> array_type_vec;

bool sem_array_type::operator==(const sem_array_type &rhs) const {
    if (ele_type != rhs.ele_type) {
        return false;
    }
    if (dim != rhs.dim) {
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

sem_array_type sem::make_array_type_from_exp_seq(ast_exp_seq *seq) {
    const sem_type &ch_t = (*seq->get_exp_vec().begin())->get_type();
    int range_id = get_or_define_range_type(make_int_range_type(1, seq->get_size()));
    sem_array_type ret = {{false}, 0, {range_id}};

    if (ch_t.tg == type_group::ARRAY) {
        const sem_array_type &e_t = sem::get_array_type_by_idx(ch_t.id);
        ret.ele_type = e_t.ele_type;
        ret.dim = e_t.dim + 1;
        ret.range_vec.insert(
                ret.range_vec.end(), e_t.range_vec.begin(), e_t.range_vec.end()
        );
    } else {
        ret.ele_type = ch_t;
        ret.dim = 1;
    }

    return ret;
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

bool sem::array_can_assign(const sem_type &type_l, const sem_type &type_r) {
    const sem_array_type &a_l = get_array_type_by_idx(type_l.id);
    const sem_array_type &a_r = get_array_type_by_idx(type_r.id);

    if (a_l.dim != a_r.dim) {
        return false;
    }
    for (int i = 0; i < a_l.dim; i++) {
        const sem_range_type &r_l = get_range_type_by_idx(a_l.range_vec[i]);
        const sem_range_type &r_r = get_range_type_by_idx(a_r.range_vec[i]);
        if (get_range_length(r_l) != get_range_length(r_r)) {
            return false;
        }
    }
    return can_assign(a_l.ele_type, a_r.ele_type);
}
