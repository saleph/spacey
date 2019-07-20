#ifndef SPACEY_ACTIVATION_HPP
#define SPACEY_ACTIVATION_HPP

#include <common/include/FloatingPointUtils.hpp>

namespace spacey::neat {

struct Activation {
    long double value;
};

inline auto operator==(const Activation first, const Activation second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator<<(std::ostream& os, const Activation response) -> std::ostream & {
    os << response.value;
    return os;
}

}

#endif //SPACEY_ACTIVATION_HPP
