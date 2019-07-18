#ifndef SPACEY_WEIGHTED_ACTIVATION_HPP
#define SPACEY_WEIGHTED_ACTIVATION_HPP

#include "common/include/FloatingPointUtils.hpp"

namespace spacey::neat {

struct WeightedActivation {
    long double value;

    auto operator+=(const WeightedActivation other) -> WeightedActivation& {
        value += other.value;
        return *this;
    }
};

inline auto operator==(const WeightedActivation first, const WeightedActivation second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator+(const WeightedActivation first, const WeightedActivation second) -> WeightedActivation {
    return { first.value + second.value };
}

}

#endif //SPACEY_WEIGHTED_ACTIVATION_HPP
