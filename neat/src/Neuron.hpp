#ifndef SPACEY_NEURON_HPP
#define SPACEY_NEURON_HPP

#include <fruit/fruit.h>
#include <gsl/gsl>
#include <boost/functional/hash.hpp>
#include <neat/src/Response.hpp>
#include <neat/src/WeightedActivation.hpp>
#include <neat/src/NeuronInput.hpp>

namespace spacey::neat {
class Neuron;
using ObservedNeuronList = std::vector<gsl::not_null<Neuron*>>;
using NeuronInputs = std::vector<NeuronInput>;
using NeuronList = std::vector<std::unique_ptr<Neuron>>;

class Neuron {
    friend auto operator==(const Neuron& first, const Neuron& second) -> bool;
    friend std::hash<Neuron>;
public:
    static auto activationFunction(WeightedActivation activation) -> Response;

    explicit Neuron(const NeuronList& validNeuronInputs);
    explicit Neuron(NeuronInputs inputs, const NeuronList& validNeuronInputs);
    void verifyIfInputsContainNoneOf(const NeuronInputs& additionalInputs);
    void verifyIfValidNeuronInputsContains(const NeuronInputs& additionalInputs);
    Neuron(const Neuron& other) = delete;
    Neuron(Neuron&& other) noexcept = default;
    ~Neuron() = default;
    auto operator=(const Neuron& other) -> Neuron& = delete;
    auto operator=(Neuron&& other) -> Neuron& = default;

    void addInputs(const NeuronInputs& additionalInputs);
    [[nodiscard]] auto getInputs() const -> const NeuronInputs&;
    /// Assignment operator for batch processing of the Neurons
    /// during forward propagation
    auto operator=(Response response) noexcept -> Neuron&;
    void setResponse(Response response);
    [[nodiscard]] auto getResponse() const -> Response;

private:
    NeuronInputs inputs{};
    Response response{ 0.0L };
    const NeuronList& validNeuronInputs;
};

auto operator==(const Neuron& first, const Neuron& second) -> bool;
auto operator!=(const Neuron& first, const Neuron& second) -> bool;
} // namespace spacey::neat

namespace std {  // NOLINT(cert-dcl58-cpp) standard hash injection
template <>
struct hash<spacey::neat::Neuron> {
    auto operator()(const spacey::neat::Neuron& n) const noexcept -> size_t {
        size_t seed = 0;
        boost::hash_combine(seed, n.response.value);
        std::for_each(std::begin(n.inputs), std::end(n.inputs), [&seed](auto&& input) {
            boost::hash_combine(seed, input);
        });
        boost::hash_combine(seed, n.inputs);
        return seed;
    }
};
}

#endif //SPACEY_NEURON_HPP
