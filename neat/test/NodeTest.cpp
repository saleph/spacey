#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gsl/gsl>
#include "neat/src/Neuron.hpp"

namespace spacey::neat {
using Neuron::NeuronReferenceList;
using ::testing::UnorderedElementsAre;

class NeuronTestFixture : public ::testing::Test {
public:
    NeuronReferenceList neuronRefList;
};

TEST_F(NeuronTestFixture, shouldTwoNeuronsInSameStateBeDifferent) {
    auto firstNeuron = Neuron{neuronRefList};
    auto secondNeuron = Neuron{neuronRefList};
    ASSERT_TRUE(firstNeuron != secondNeuron, "Neuron in the same state should not be treated as equals");
}

}
