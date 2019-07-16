#ifndef SPACEY_NET_HPP
#define SPACEY_NET_HPP

#include <vector>
#include <unordered_map>
#include "neat/src/Activation.hpp"
#include "neat/src/Response.hpp"
#include "neat/src/Neuron.hpp"
#include "neat/src/NetInput.hpp"

namespace spacey::neat {

class Net {
public:
    Net() = delete;
    Net(std::size_t inputSize, std::size_t outputSize);

    auto addNeuron() -> Neuron&;
    auto getNetResponseFor(const std::vector<NetInput>& inputs) -> std::vector<Response>;

private:
    using VisitedNeuronsMap = std::unordered_map<Neuron, bool>;
    std::vector<std::unique_ptr<Neuron>> neurons;
    ObservedNeuronList netInputs;
    ObservedNeuronList netOutputs;

    void calculateResponseFor(Neuron& neuron, VisitedNeuronsMap& visited);
};

}

#endif // SPACEY_NET_HPP