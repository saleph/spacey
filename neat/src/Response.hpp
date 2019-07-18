#ifndef SPACEY_RESPONSE_HPP
#define SPACEY_RESPONSE_HPP

#include "common/include/FloatingPointUtils.hpp"

namespace spacey::neat {

struct Response {
    long double value;
};

inline auto operator==(const Response first, const Response second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

}

#endif //SPACEY_RESPONSE_HPP
