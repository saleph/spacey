#ifndef SPACEY_NET_HPP
#define SPACEY_NET_HPP

#include <vector>
#include <unordered_map>
#include <gsl/gsl>
#include <neat/src/Response.hpp>
#include <neat/src/Neuron.hpp>
#include <neat/src/NetInput.hpp>

namespace spacey::neat {
class Net {
public:
    struct InputSize {
        std::size_t value;
    };
    struct OutputSize {
        std::size_t value;
    };

    Net() = delete;
    explicit Net(InputSize inputSize, OutputSize outputSize);

    [[nodiscard]] auto getNetInputs() const -> const ObservedNeuronList&;
    [[nodiscard]] auto getNetOutputs() const -> const ObservedNeuronList&;
    [[nodiscard]] auto addNeuron() -> gsl::not_null<Neuron*>;

    [[nodiscard]] auto getNetResponseFor(const std::vector<NetInput>& inputs) -> std::vector<Response>;

private:
    using VisitedNeuronsMap = std::unordered_map<Neuron*, bool>;
    NeuronList neurons;
    ObservedNeuronList netInputs;
    ObservedNeuronList netOutputs;

    void calculateResponseFor(Neuron& neuron, VisitedNeuronsMap& visited);
};

}

#endif // SPACEY_NET_HPP