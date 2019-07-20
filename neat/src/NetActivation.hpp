#ifndef SPACEY_NET_ACTIVATION_HPP
#define SPACEY_NET_ACTIVATION_HPP

#include "common/include/FloatingPointUtils.hpp"

namespace spacey::neat {

struct NetActivation {
    long double value;
};

inline auto operator==(const NetActivation first, const NetActivation second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator*(const NetActivation netInput, const Weight weight) -> WeightedActivation {
    return { netInput.value * weight.value };
}

}

#endif //SPACEY_NET_ACTIVATION_HPP
