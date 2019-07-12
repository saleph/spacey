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
        neuronRefList.clear();
    }

    NeuronReferenceList neuronRefList;
};

TEST_F(NeuronTestFixture, shouldANeuronHoldReferenceToListOfItsInputs) {
    auto neuron = Neuron{ neuronRefList };
    neuronRefList.push_back(neuron);
    ASSERT_EQ(neuron.getInputs().at(0), neuron) <<
            "Neuron should hold reference to list with it's inputs";
}

TEST_F(NeuronTestFixture, shouldTwoNeuronsInSameStateBeDifferent) {
    const auto firstNeuron = Neuron{ neuronRefList };
    const auto secondNeuron = Neuron{ neuronRefList };
    ASSERT_TRUE(firstNeuron != secondNeuron) <<
            "Neuron in the same state should not be treated as equals";
}

TEST_F(NeuronTestFixture, shouldNeuronBeAbleToHoldItselfInInputList) {
    auto neuron = Neuron{ neuronRefList };
    auto&& message = "Neuron should be able to hold ref to itself in inputs";
    ASSERT_NO_THROW(neuronRefList.push_back(neuron)) << message;
    ASSERT_THAT(neuron.getInputs(), UnorderedElementsAre(std::ref(neuron))) << message;
}

}
