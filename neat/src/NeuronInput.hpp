#ifndef SPACEY_NEURON_INPUT_HPP
#define SPACEY_NEURON_INPUT_HPP

#include "neat/src/Weight.hpp"

namespace spacey::neat {

class Neuron;
struct NeuronInput {
    Neuron* input;
    Weight weight;
};

inline auto operator==(const NeuronInput first, const NeuronInput second) -> bool {
    return first.input == second.input && first.weight == second.weight;
}

}

#endif //SPACEY_NEURON_INPUT_HPP
