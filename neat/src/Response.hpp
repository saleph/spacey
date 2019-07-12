#ifndef SPACEY_RESPONSE_HPP
#define SPACEY_RESPONSE_HPP

#include <cmath>
#include <limits>

namespace spacey::neat {

struct Response {
    double value;
};

inline auto operator==(const Response& first, const Response& second) -> bool {
    return std::fabs(first.value - second.value) < std::numeric_limits<double>::epsilon();
}

}

#endif //SPACEY_RESPONSE_HPP
