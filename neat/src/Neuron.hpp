#ifndef SPACEY_NEURON_HPP
#define SPACEY_NEURON_HPP

#include <functional>
#include <atomic>
#include <fruit/fruit.h>
#include <gsl/gsl>
#include <boost/functional/hash.hpp>
#include "neat/src/Response.hpp"
#include "neat/src/WeightedActivation.hpp"
#include "neat/src/NeuronInput.hpp"

namespace spacey::neat {
class Neuron;
using ObservedNeuronList = std::vector<Neuron*>;
using NeuronInputs = std::vector<NeuronInput>;

class Neuron {
    friend auto operator==(const Neuron& first, const Neuron& second) -> bool;
    friend std::hash<Neuron>;
    static std::atomic_size_t neuronCounter;
public:
    static auto activationFunction(const WeightedActivation activation) -> Response;

    Neuron() = default;
    explicit Neuron(NeuronInputs inputs);

    auto addInput(NeuronInput input) -> NeuronInput&;
    [[nodiscard]] auto getInputs() const -> const NeuronInputs&;
    /// Assignment operator for batch processing of the Neurons
    /// during forward propagation
    auto operator=(const Response response) noexcept -> Neuron&;
    void setResponse(const Response response);
    [[nodiscard]] auto getResponse() const -> Response;

private:
    const std::size_t id = ++neuronCounter;
    NeuronInputs inputs{};
    Response response{ 0.0L };
};

auto operator==(const Neuron& first, const Neuron& second) -> bool;
auto operator!=(const Neuron& first, const Neuron& second) -> bool;
} // namespace spacey::neat

namespace std {  // NOLINT(cert-dcl58-cpp) standard hash injection
template <>
struct hash<spacey::neat::Neuron> {
    auto operator()(const spacey::neat::Neuron& n) const noexcept -> size_t {
        size_t seed = 0;
        boost::hash_combine(seed, n.id);
        boost::hash_combine(seed, n.response.value);
        boost::hash_combine(seed, &n.inputs);
        return seed;
    }
};
}

#endif //SPACEY_NEURON_HPP
