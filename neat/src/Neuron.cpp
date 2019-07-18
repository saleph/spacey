#include <cmath>
#include <algorithm>
#include <neat/src/Neuron.hpp>

namespace spacey::neat {

auto Neuron::activationFunction(const WeightedActivation activation) -> Response {
    return { tanh(activation.value) };
}

Neuron::Neuron(const NeuronList& validNeuronInputs) 
    : validNeuronInputs{ validNeuronInputs } {
}

Neuron::Neuron(NeuronInputs inputs, const NeuronList& validNeuronInputs)
    : inputs{ std::move(inputs) }, validNeuronInputs{ validNeuronInputs } {
}

void Neuron::addInputs(const NeuronInputs& additionalInputs) {
    verifyIfValidNeuronInputsContains(additionalInputs);
    verifyIfInputsContainNoneOf(additionalInputs);
    inputs.insert(std::end(inputs), std::begin(additionalInputs), std::end(additionalInputs));
}

void Neuron::verifyIfValidNeuronInputsContains(const NeuronInputs& additionalInputs) {
    Expects(std::all_of(std::begin(additionalInputs), std::end(additionalInputs), [this](auto&& input) {
        return std::any_of(std::begin(validNeuronInputs), std::end(validNeuronInputs), [&input](auto&& validInput) {
            return input.input == validInput.get();
        });
    }));
}

void Neuron::verifyIfInputsContainNoneOf(const NeuronInputs& additionalInputs) {
    Expects(std::none_of(std::begin(additionalInputs), std::end(additionalInputs), [this](auto&& additionalInput) {
        return std::find(std::begin(inputs), std::end(inputs), additionalInput) != std::end(inputs);
    }));
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
