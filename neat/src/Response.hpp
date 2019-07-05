#ifndef SPACEY_RESPONSE_HPP
#define SPACEY_RESPONSE_HPP

#include <cmath>
#include <limits>

namespace spacey::neat {

struct Response {
    double value;
    auto operator==(const Response& other) const {
        return std::fabs(value - other.value) < std::numeric_limits<double>::epsilon();
    }
};

}

#endif //SPACEY_RESPONSE_HPP
