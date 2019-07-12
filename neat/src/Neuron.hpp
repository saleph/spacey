#ifndef SPACEY_NEURON_HPP
#define SPACEY_NEURON_HPP

#include <functional>
#include <atomic>
#include <fruit/fruit.h>
#include <gsl/gsl>
#include "neat/src/Response.hpp"

namespace spacey::neat {
class Neuron;
using NeuronReferenceList = std::vector<std::reference_wrapper<Neuron>>;

class Neuron {
    friend auto operator==(const Neuron& first, const Neuron& second) -> bool;
    static std::atomic_size_t neuronCounter;
public:
    /// Strictly for sparse_map usage.
    ///
    /// @return Neuron instance that will never occur naturally
    static auto getNeverAppearingNeuronInstance();

    Neuron()
        : inputs(NeuronReferenceList{}) {}
    explicit Neuron(const NeuronReferenceList& inputs);
    /// Neurons should not be copied as they contains reference
    /// to list of it's inputs. Copy constructor would be
    /// misleading.
    Neuron(const Neuron& other) = delete;
    Neuron(Neuron&& other) = delete;
    ~Neuron() noexcept = default;
    Neuron& operator=(const Neuron& other) = delete;
    Neuron& operator=(Neuron&& other) = delete;

    [[nodiscard]] auto getInputs() const -> const NeuronReferenceList&;
    /// Assignment operator for batch processing of the Neurons
    /// during forward propagation
    Neuron& operator=(const Response response) noexcept;
    void setResponse(const Response response);
    [[nodiscard]] auto getResponse() const -> Response;



private:
    const std::size_t id = ++neuronCounter;
    const NeuronReferenceList& inputs;
    Response response{ 0.0L };

    explicit Neuron(const std::size_t id, const NeuronReferenceList& inputs);
};

auto operator==(const Neuron& first, const Neuron& second) -> bool;
auto operator!=(const Neuron& first, const Neuron& second) -> bool;

}

#endif //SPACEY_NEURON_HPP
