#ifndef SPACEY_NET_UTILS_HPP
#define SPACEY_NET_UTILS_HPP

#include <cstddef>

namespace spacey::neat::net_utils {

struct InputSize {
    std::size_t value;
};

struct OutputSize {
    std::size_t value;
};

inline auto operator<<(std::ostream& os, const InputSize inputSize) -> std::ostream& {
    os << inputSize.value;
    return os;
}

inline auto operator<<(std::ostream& os, const OutputSize outputSize) -> std::ostream& {
    os << outputSize.value;
    return os;
}

}

#endif //SPACEY_NET_UTILS_HPP