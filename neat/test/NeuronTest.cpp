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
        neuronInputs.clear();
    }

    Weight defaultWeight{ 1.0L };
    NeuronInputs neuronInputs;
};

TEST_F(NeuronTestFixture, shouldANeuronHoldReferenceToListOfItsInputs) {
    auto neuron = Neuron{ neuronInputs };
    neuronInputs.emplace_back(&neuron, defaultWeight);
    ASSERT_THAT(neuron.getInputs(), 
        UnorderedElementsAre(std::pair{ gsl::not_null(&neuron), defaultWeight }))
        << "Neuron should hold reference to list with it's inputs";
}

TEST_F(NeuronTestFixture, shouldTwoNeuronsInSameStateBeDifferent) {
    const auto firstNeuron = Neuron{ neuronInputs };
    const auto secondNeuron = Neuron{ neuronInputs };
    ASSERT_TRUE(firstNeuron != secondNeuron)
        << "Neuron in the same state should not be treated as equals";
}

TEST_F(NeuronTestFixture, shouldNeuronBeAbleToHoldItselfInInputList) {
    auto neuron = Neuron{ neuronInputs };
    auto&& message = "Neuron should be able to hold ref to itself in inputs";
    ASSERT_NO_THROW(neuronInputs.emplace_back(&neuron, defaultWeight)) << message;
    ASSERT_THAT(neuron.getInputs(),
        UnorderedElementsAre(std::pair{ gsl::not_null(&neuron), defaultWeight }))
        << message;
}

}
