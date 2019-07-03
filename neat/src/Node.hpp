#ifndef SPACEY_NODE_HPP
#define SPACEY_NODE_HPP

#include <fruit/fruit.h>
#include <gsl/gsl>
#include "Activation.h"

namespace spacey::neat {

class Node {
public:
    auto getOutputNodes() -> std::vector<gsl::not_null<Node*>>;
    auto addOutputNode(const gsl::not_null<Node*> node) -> void;
    auto removeOutputNode(const gsl::not_null<Node*> node) -> void;

private:
    std::vector<gsl::not_null<Node*>> inputs;
    std::vector<gsl::not_null<Node*>> outputs;
    Activation activationFunctionResult{ 0.0 };
};

}

#endif //SPACEY_NODE_HPP
