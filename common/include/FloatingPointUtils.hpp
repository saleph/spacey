#ifndef SPACEY_FLOATING_POINT_UTILS_HPP
#define SPACEY_FLOATING_POINT_UTILS_HPP

#include <cmath>
#include <limits>

namespace spacey::common {

inline auto areFloatingPointEquals(const long double& first, const long double& second) -> bool {
    return std::fabs(first - second) < std::numeric_limits<long double>::epsilon();
}

}

#endif //SPACEY_FLOATING_POINT_UTILS_HPP
