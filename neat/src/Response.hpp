#ifndef SPACEY_RESPONSE_HPP
#define SPACEY_RESPONSE_HPP

#include <common/include/FloatingPointUtils.hpp>
#include <iostream>
#include <iomanip>

namespace spacey::neat {

struct Response {
    long double value;
};

inline auto operator==(const Response first, const Response second) -> bool {
    std::cout << std::setprecision(20) << first.value << " ==\n" << second.value << ", eq?: " <<
        common::areFloatingPointEquals(first.value, second.value) << std::endl;
    return common::areFloatingPointEquals(first.value, second.value);
}

inline auto operator<<(std::ostream& os, const Response response) -> std::ostream& {
    os << response.value;
    return os;
}

}

#endif //SPACEY_RESPONSE_HPP
