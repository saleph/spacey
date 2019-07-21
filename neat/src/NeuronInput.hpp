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

inline auto operator<<(std::ostream& os, const NeuronInput input) -> std::ostream& {
    os << "{ " << input.input << ", " << input.weight << "}" << std::endl;
    return os;
}

}

#endif //SPACEY_NEURON_INPUT_HPP
