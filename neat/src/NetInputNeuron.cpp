#include <cmath>
#include <algorithm>
#include <neat/src/NetInputNeuron.hpp>

namespace spacey::neat {

NetInputNeuron::NetInputNeuron(const NeuronList& validNeuronInputs)
    : Neuron(validNeuronInputs) {
}

void NetInputNeuron::addInputs(const NeuronInputs& additionalInputs) {
    throw std::logic_error("you can't add any NeuronInput to the NetInputNeuron");
}

}
