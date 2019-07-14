#include "neat/src/Net.hpp"
#include <algorithm>
#include <numeric>
#include <boost/iterator/indirect_iterator.hpp>
#include "neat/src/Neuron.hpp"
#include "neat/src/Weight.hpp"

namespace spacey::neat {

auto Net::getNetResponseFor(const std::vector<NetInput>& inputs) -> std::vector<Response> {
    auto indirectNetInputs = boost::indirect_iterator<ObservedNeuronList::iterator, Neuron>(netInputs.begin());
    std::transform(std::begin(inputs), std::end(inputs), indirectNetInputs, [](auto&& input) {
        // no scaling of the input
        const auto inputWeight = Weight{ 1.0L };
        return Neuron::activationFunction(input * inputWeight);
    });
    VisitedNeuronsMap visited;
    std::for_each(std::begin(netInputs), std::end(netInputs), [&visited](auto&& node) {
        // after setting the responses of the inputNodes, set them to be visited ones
        // this will stop the recursion
        visited[*node] = true;
    });
    std::for_each(std::begin(netOutputs), std::end(netOutputs), [this, &visited](auto&& node) {
        // propagate the input with DFS
        calculateResponseFor(*node, visited);
    });
    std::vector<Response> responses;
    std::transform(std::begin(netOutputs), std::end(netOutputs), std::back_inserter(responses), [](auto&& node) {
        return node->getResponse();
    });
    return responses;
}

void Net::calculateResponseFor(Neuron& neuron, VisitedNeuronsMap& visited) {
    auto&& inputs = neuron.getInputs();
    std::for_each(std::begin(inputs), std::end(inputs), [this, &visited](auto&& input) {
        auto& [inputNeuron, inputNeuronWeight] = input;
        if (!visited[*inputNeuron]) {
            visited[*inputNeuron] = true;
            calculateResponseFor(*inputNeuron, visited);
        }
    });
    // note: input.response may be read for nodes that are marked visited, but not
    // calculated yet. That's normal, it's just a cycle in the network, it will
    // behave like a recurrent neuron (it will use value from previous evaluation)
    const auto weightedActivation = std::transform_reduce(std::begin(inputs), std::end(inputs), WeightedActivation{ 0.0L },
            std::plus<>(), [](auto&& input) {
            auto& [inputNeuron, inputNeuronWeight] = input;
        return inputNeuron->getResponse() * inputNeuronWeight;
    });
    neuron.setResponse(Neuron::activationFunction(weightedActivation));
}

}
