#include <cmath>
#include "neat/src/Neuron.hpp"

namespace spacey::neat {

auto Neuron::activationFunction(const WeightedActivation activation) -> Response {
    return { tanh(activation.value) };
}

Neuron::Neuron(NeuronInputs inputs)
    : inputs{ std::move(inputs) } {
}

auto Neuron::addInput(NeuronInput input) -> NeuronInput& {
    return inputs.emplace_back(input);
}

auto Neuron::getInputs() const -> const NeuronInputs& {
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

auto operator==(const Neuron& first, const Neuron& second) -> bool {
    return (&first == &second) || (first.response == second.response && first.inputs == second.inputs);
}

auto operator!=(const Neuron& first, const Neuron& second) -> bool {
    return !operator==(first, second);
}

}
