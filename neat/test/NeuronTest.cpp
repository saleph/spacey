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
    Response nonDefaultResponse{ 22.33L };
};

TEST_F(NeuronTestFixture, shouldTwoNeuronsInSameStateBeTheSame) {
    const auto firstNeuron = Neuron{};
    const auto secondNeuron = Neuron{};
    ASSERT_TRUE(firstNeuron == secondNeuron);
}

TEST_F(NeuronTestFixture, shouldNeuronBeAbleToHoldReferenceToItsInputNeuron) {
    auto neuron = Neuron{};
    auto inputNeuron = Neuron{};
    const auto input = NeuronInput{ &inputNeuron, defaultWeight };
    neuron.addInput(input);
    inputNeuron.setResponse({ nonDefaultResponse });
    ASSERT_THAT(neuron.getInputs(), UnorderedElementsAre(input));
}

TEST_F(NeuronTestFixture, shouldNeuronBeAbleToHoldItselfInInputList) {
    auto neuron = Neuron{};
    const auto input = NeuronInput{ &neuron, defaultWeight };
    ASSERT_NO_THROW(neuron.addInput(input));
    ASSERT_THAT(neuron.getInputs(), UnorderedElementsAre(input));
}

}
