#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gsl/gsl>
#include <neat/src/Neuron.hpp>
#include "neat/src/NetInputNeuron.hpp"

namespace spacey::neat {
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;

class NeuronTestFixture : public ::testing::Test {
public:
    void TearDown() override {
        validNeurons.clear();
    }

    auto getRegisteredNeuron() -> Neuron& {
        auto& neuron = validNeurons.emplace_back(std::make_unique<Neuron>(validNeurons));
        return *neuron;
    }

    auto getRegisteredNetInputNeuron() -> Neuron& {
        auto& neuron = validNeurons.emplace_back(std::make_unique<NetInputNeuron>(validNeurons));
        return *neuron;
    }

    Weight defaultWeight{ 1.0L };
    Response nonDefaultResponse{ 22.33L };
    NeuronList validNeurons;
};

TEST_F(NeuronTestFixture, shouldTwoNeuronsInSameStateBeTheSame) {
    const auto& firstNeuron = getRegisteredNeuron();
    const auto& secondNeuron = getRegisteredNeuron();
    ASSERT_TRUE(firstNeuron == secondNeuron);
}

TEST_F(NeuronTestFixture, shouldNeuronBeAbleToHoldReferenceToItsInputNeuron) {
    auto& neuron = getRegisteredNeuron();
    auto& inputNeuron = getRegisteredNeuron();
    const auto input = NeuronInput{ &inputNeuron, defaultWeight };
    neuron.addInputs({ input });
    inputNeuron.setResponse(nonDefaultResponse);
    ASSERT_THAT(neuron.getInputs(), UnorderedElementsAre(input));
}

TEST_F(NeuronTestFixture, shouldNeuronBeAbleToHoldItselfInInputList) {
    auto& neuron = getRegisteredNeuron();
    const auto input = NeuronInput{ &neuron, defaultWeight };
    ASSERT_NO_THROW(neuron.addInputs({ input }));
    ASSERT_THAT(neuron.getInputs(), UnorderedElementsAre(input));
}

TEST_F(NeuronTestFixture, shouldThrowWhenAddingInputNeuronOutOfRegisteredOnes) {
    auto& neuron = getRegisteredNeuron();
    auto notRegisteredNeuron = Neuron{ validNeurons };
    const auto input = NeuronInput{ &notRegisteredNeuron, defaultWeight };
    ASSERT_THROW(neuron.addInputs({ input }), gsl::fail_fast);
}

TEST_F(NeuronTestFixture, shouldThrowWhenAddingInputThatAlreadyExists) {
    auto& neuron = getRegisteredNeuron();
    const auto input = NeuronInput{ &neuron, defaultWeight };
    ASSERT_NO_THROW(neuron.addInputs({ input }));
    ASSERT_THROW(neuron.addInputs({ input }), gsl::fail_fast);
}

TEST_F(NeuronTestFixture, shouldThrowWhenAddingInputToNetInputNeuron) {
    auto& neuron = getRegisteredNetInputNeuron();
    const auto input = NeuronInput{ &neuron, defaultWeight };
    ASSERT_THROW(neuron.addInputs({ input }), std::logic_error);
}

}
