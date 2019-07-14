#ifndef SPACEY_NEURON_HPP
#define SPACEY_NEURON_HPP

#include <functional>
#include <atomic>
#include <fruit/fruit.h>
#include <gsl/gsl>
#include <boost/functional/hash.hpp>
#include "neat/src/Response.hpp"
#include "neat/src/WeightedActivation.hpp"
#include "neat/src/Weight.hpp"

namespace spacey::neat {
class Neuron;
using ObservedNeuronList = std::vector<gsl::not_null<Neuron*>>;
using NeuronInputs = std::vector<std::pair<gsl::not_null<Neuron*>, Weight>>;

class Neuron {
    friend auto operator==(const Neuron& first, const Neuron& second) -> bool;
    friend std::hash<Neuron>;
    static std::atomic_size_t neuronCounter;
public:
    static auto activationFunction(const WeightedActivation activation) -> Response;

    explicit Neuron(const NeuronInputs& inputs);
    /// Neurons should not be copied as they contains reference
    /// to list of it's inputs. Copy constructor would be
    /// misleading.
    Neuron(const Neuron& other) = delete;
    /// Neurons should not be copied nor moved as they contains reference
    /// to list of it's inputs. Copy constructor would be
    /// misleading.
    Neuron(Neuron&& other) = delete;
    ~Neuron() noexcept = default;
    Neuron& operator=(const Neuron& other) = delete;
    Neuron& operator=(Neuron&& other) = delete;

    [[nodiscard]] auto getInputs() const -> const NeuronInputs&;
    /// Assignment operator for batch processing of the Neurons
    /// during forward propagation
    Neuron& operator=(const Response response) noexcept;
    void setResponse(const Response response);
    [[nodiscard]] auto getResponse() const -> Response;

private:
    const std::size_t id = ++neuronCounter;
    const NeuronInputs& inputs;
    Response response{ 0.0L };

    explicit Neuron(const std::size_t id, const NeuronInputs& inputs);
};

auto operator==(const Neuron& first, const Neuron& second) -> bool;
auto operator!=(const Neuron& first, const Neuron& second) -> bool;
}

namespace std {  // NOLINT(cert-dcl58-cpp) standard hash injection
using ::spacey::neat::Neuron;
template <>
struct hash<Neuron> {
    auto operator()(const Neuron& n) const noexcept -> size_t {
        size_t seed = 0;
        boost::hash_combine(seed, n.id);
        boost::hash_combine(seed, n.response.value);
        boost::hash_combine(seed, &n.inputs);
        return seed;
    }
};
}

#endif //SPACEY_NEURON_HPP
