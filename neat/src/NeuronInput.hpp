#ifndef SPACEY_NEURON_INPUT_HPP
#define SPACEY_NEURON_INPUT_HPP

#include <boost/functional/hash.hpp>
#include <neat/src/Weight.hpp>

namespace spacey::neat {

class Neuron;
struct NeuronInput {
    Neuron* input;
    Weight weight;
};

inline auto operator==(const NeuronInput first, const NeuronInput second) -> bool {
    return first.input == second.input && first.weight == second.weight;
}

// ReSharper disable once CppInconsistentNaming
inline auto hash_value(const spacey::neat::NeuronInput input) {
    std::size_t seed = 0;
    boost::hash_combine(seed, input.input);
    boost::hash_combine(seed, input.weight.value);
    return seed;
}
}

#endif //SPACEY_NEURON_INPUT_HPP
