#ifndef SPACEY_RESPONSE_HPP
#define SPACEY_RESPONSE_HPP

#include <iostream>
#include <common/include/FloatingPointUtils.hpp>

namespace spacey::neat {

struct Response {
    long double value;
};

inline auto operator==(const Response first, const Response second) -> bool {
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator<<(std::ostream& os, const Response response) -> std::ostream& {
    os << response.value;
    return os;
}

}

#endif //SPACEY_RESPONSE_HPP
