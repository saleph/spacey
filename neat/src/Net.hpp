#ifndef SPACEY_NET_HPP
#define SPACEY_NET_HPP

#include <vector>
#include <unordered_map>
#include <gsl/gsl>
#include <neat/src/Response.hpp>
#include <neat/src/Neuron.hpp>
#include <neat/src/NetActivation.hpp>
#include <neat/src/NetUtils.hpp>

namespace spacey::neat {
using net_utils::InputSize;
using net_utils::OutputSize;

class Net {
public:
    Net() = delete;
    explicit Net(InputSize inputSize, OutputSize outputSize);

    [[nodiscard]] auto getNetInputs() const -> const ObservedNeuronList&;
    [[nodiscard]] auto getNetOutputs() const -> const ObservedNeuronList&;
    [[nodiscard]] auto addNeuron() -> gsl::not_null<Neuron*>;

    [[nodiscard]] auto getNetResponseFor(const std::vector<NetActivation>& inputs) -> std::vector<Response>;

private:
    using VisitedNeuronsMap = std::unordered_map<Neuron*, bool>;
    NeuronList neurons;
    ObservedNeuronList netInputs;
    ObservedNeuronList netOutputs;

    void insertNetInputValues(const std::vector<NetActivation>& inputs);
    void markNetInputsAsVisited(VisitedNeuronsMap& visited);
    void propagateNetInputs(VisitedNeuronsMap& visited);
    void calculateResponseFor(Neuron& neuron, VisitedNeuronsMap& visited);
    [[nodiscard]] auto gatherOutputsResponses() -> std::vector<Response>;
};

}

#endif // SPACEY_NET_HPP