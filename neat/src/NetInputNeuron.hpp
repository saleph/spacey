#ifndef SPACEY_NET_INPUT_NEURON_HPP
#define SPACEY_NET_INPUT_NEURON_HPP

#include <gsl/gsl>
#include <neat/src/Neuron.hpp>

namespace spacey::neat {

class NetInputNeuron final : public Neuron {
public:
    explicit NetInputNeuron(const NeuronList& validNeuronInputs);
    virtual ~NetInputNeuron() = default;

    void addInputs(const NeuronInputs& additionalInputs) override;
};
}

#endif //SPACEY_NET_INPUT_NEURON_HPP
