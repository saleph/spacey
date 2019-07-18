#ifndef SPACEY_NET_INPUT_HPP
#define SPACEY_NET_INPUT_HPP

#include "common/include/FloatingPointUtils.hpp"

namespace spacey::neat {

struct NetInput {
    long double value;
};

inline auto operator==(const NetInput first, const NetInput second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator*(const NetInput netInput, const Weight weight) -> WeightedActivation {
    return { netInput.value * weight.value };
}

}

#endif //SPACEY_NET_INPUT_HPP
