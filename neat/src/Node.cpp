#include <algorithm>
#include "Node.hpp"

namespace spacey::neat {

auto Node::addOutputNode(const gsl::not_null<Node*> node) -> void {
    outputs.emplace_back(node);
}

auto Node::removeOutputNode(const gsl::not_null<Node*> node) -> void {
    outputs.erase(std::remove(std::begin(outputs), std::end(outputs), node), std::end(outputs));
}

auto Node::getOutputNodes() -> std::vector<gsl::not_null<Node*>> {
    return outputs;
}

}
