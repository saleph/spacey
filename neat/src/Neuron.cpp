#include <algorithm>
#include <limits>
#include "neat/src/Neuron.hpp"

namespace spacey::neat {
std::atomic_size_t Neuron::neuronCounter = 0u;

auto Neuron::getNeverAppearingNeuronInstance() {
    static const NeuronReferenceList dummyInputsList;
    return Neuron(std::numeric_limits<std::size_t>::max(), dummyInputsList);
}

Neuron::Neuron(const NeuronReferenceList& inputs)
    : inputs{ inputs }
{ }

auto Neuron::getInputs() const -> const NeuronReferenceList& {
    return inputs;
}

Neuron& Neuron::operator=(const Response response) noexcept {
    this->response = response;
    return *this;
}

void Neuron::setResponse(const Response response) {
    this->response = response;
}

auto Neuron::getResponse() const -> Response {
    return response;
}

Neuron::Neuron(const std::size_t id, const NeuronReferenceList& inputs)
    : id{ id }, inputs{ inputs }
{ }

auto operator==(const Neuron& first, const Neuron& second) -> bool {
    return first.id == second.id && first.response == second.response && &first.inputs == &second.inputs;
}

auto operator!=(const Neuron& first, const Neuron& second) -> bool {
    return !operator==(first, second);
}

}
