#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gsl/gsl>
#include "neat/src/Neuron.hpp"

namespace spacey::neat {
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;

class NeuronTestFixture : public ::testing::Test {
public:
    void TearDown() override {
    }

    Weight defaultWeight{ 1.0L };
};

TEST_F(NeuronTestFixture, shouldTwoNeuronsInSameStateBeDifferent) {
    const auto firstNeuron = Neuron{};
    const auto secondNeuron = Neuron{};
    ASSERT_TRUE(firstNeuron != secondNeuron)
            << "Neuron in the same state should not be treated as equals";
}

TEST_F(NeuronTestFixture, shouldNeuronBeAbleToHoldItselfInInputList) {
    auto neuron = Neuron{};
    const auto input = NeuronInput{ &neuron, defaultWeight };
    neuron.addInput(input);
    ASSERT_THAT(neuron.getInputs(),
                UnorderedElementsAre(input))
            << "Neuron should be able to hold ref to itself in inputs";
}

}
