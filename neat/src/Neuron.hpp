#ifndef SPACEY_NEURON_HPP
#define SPACEY_NEURON_HPP

#include <functional>
#include <atomic>
#include <fruit/fruit.h>
#include <gsl/gsl>
#include "neat/src/Response.hpp"

namespace spacey::neat {

class Neuron {
    static std::atomic_size_t NEURON_COUNTER;
public:
    auto getInputs() const;

    auto operator==(const Neuron& other) const;
private:
    const std::size_t id = ++NEURON_COUNTER;
    std::vector<std::reference_wrapper<Neuron>> inputs;
    Response response{ 0.0L };
};

}

#endif //SPACEY_NEURON_HPP
