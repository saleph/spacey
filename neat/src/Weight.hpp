#ifndef SPACEY_WEIGHT_HPP
#define SPACEY_WEIGHT_HPP

#include "common/include/FloatingPointUtils.hpp"
#include "neat/src/Activation.hpp"
#include "neat/src/WeightedActivation.hpp"

namespace spacey::neat {

struct Weight {
    long double value;
};

inline auto operator==(const Weight first, const Weight second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator*(const Response response, const Weight weight) -> WeightedActivation {
    return { response.value * weight.value };
}

inline auto operator<<(std::ostream& os, const Weight response) -> std::ostream& {
    os << response.value;
    return os;
}

}

#endif //SPACEY_WEIGHT_HPP
