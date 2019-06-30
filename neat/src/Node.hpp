#ifndef SPACEY_NODE_HPP
#define SPACEY_NODE_HPP

#include <fruit/fruit.h>
#include <gsl/gsl>

namespace spacey::neat {

class Node {
public:
    INJECT(Node()) = default;

    auto getOutputNodes() const -> std::vector<gsl::not_null<Node*>>;
    auto addOutputNode(const gsl::not_null<Node*> node) -> void;
    auto removeOutputNode(const gsl::not_null<Node*> node) -> void;

private:
    std::vector<gsl::not_null<Node*>> outputs;

};

}

#endif //SPACEY_NODE_HPP
