#include <cmath>
#include "neat/src/Neuron.hpp"

namespace spacey::neat {
std::atomic_size_t Neuron::neuronCounter = 0u;

auto Neuron::activationFunction(const WeightedActivation activation) -> Response {
    return { tanh(activation.value) };
}

Neuron::Neuron(const NeuronInputs& inputs)
    : inputs{ inputs }
{ }

auto Neuron::getInputs() const -> const NeuronInputs & {
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

Neuron::Neuron(const std::size_t id, const NeuronInputs& inputs)
    : id{ id }, inputs{ inputs }
{ }

auto operator==(const Neuron& first, const Neuron& second) -> bool {
    return first.id == second.id && first.response == second.response && &first.inputs == &second.inputs;
}

auto operator!=(const Neuron& first, const Neuron& second) -> bool {
    return !operator==(first, second);
}

}
