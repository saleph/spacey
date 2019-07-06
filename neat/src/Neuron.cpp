#include <algorithm>
#include "Neuron.hpp"

namespace spacey::neat {
std::atomic_size_t Neuron::NEURON_COUNTER = 0u;

Neuron::Neuron(const Neuron::NeuronReferenceList& inputs)
    : inputs(inputs)
{ }

auto Neuron::getInputs() const {
    return inputs;
}

auto Neuron::operator==(const Neuron& other) const {
    return id == other.id && response == other.response && inputs == other.inputs;
}

}
