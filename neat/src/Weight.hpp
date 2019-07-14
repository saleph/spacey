#ifndef SPACEY_WEIGHT_HPP
#define SPACEY_WEIGHT_HPP

#include "common/include/FloatingPointUtils.hpp"
#include "neat/src/Activation.hpp"
#include "neat/src/WeightedActivation.hpp"

namespace spacey::neat {

struct Weight {
    double value;
};

inline auto operator==(const Weight first, const Weight second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator*(const Response response, const Weight weight) -> WeightedActivation {
    return { response.value * weight.value };
}

}

#endif //SPACEY_WEIGHT_HPP
