#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gsl/gsl>
#include <neat/src/Net.hpp>

namespace spacey::neat {
using ::testing::UnorderedElementsAre;

class ForwardPropagationTestFixture : public ::testing::Test {
public:
    void TearDown() override {
    }

    const std::size_t defaultInputSize{ 5 };
    const std::size_t defaultOutputSize{ 6 };
    const Weight defaultWeight{ 1.0L };
    const Weight noScaling{ defaultWeight };
    const long double inputValue = 10.0L;
    const NetActivation netActivation{ inputValue };
};

TEST_F(ForwardPropagationTestFixture, shouldNetResponseOfOutputDirectlyConnectedToInputWithoutScallingBeCorrect) {
    auto net = Net{ Net::InputSize{ 1 }, Net::OutputSize{ 1 } };
    const auto input = net.getNetInputs().front();
    auto output = net.getNetOutputs().front();
    output->addInputs({ NeuronInput{input, noScaling} });

    const auto inputResponse = Neuron::activationFunction({ inputValue });
    const auto expectedOutput = Neuron::activationFunction(inputResponse * noScaling);
    ASSERT_THAT(net.getNetResponseFor({ NetActivation{inputValue} }), UnorderedElementsAre(expectedOutput));
}

TEST_F(ForwardPropagationTestFixture, should1to1WithoutScallingBeTheSameForMultipleRuns) {
    auto net = Net{ Net::InputSize{ 1 }, Net::OutputSize{ 1 } };
    const auto input = net.getNetInputs().front();
    auto output = net.getNetOutputs().front();
    output->addInputs({ NeuronInput{input, noScaling} });

    const auto inputResponse = Neuron::activationFunction({ inputValue });
    const auto expectedOutput = Neuron::activationFunction(inputResponse * noScaling);
    ASSERT_THAT(net.getNetResponseFor({ NetActivation{inputValue} }), UnorderedElementsAre(expectedOutput));
    ASSERT_THAT(net.getNetResponseFor({ NetActivation{inputValue} }), UnorderedElementsAre(expectedOutput));
    ASSERT_THAT(net.getNetResponseFor({ NetActivation{inputValue} }), UnorderedElementsAre(expectedOutput));
}

TEST_F(ForwardPropagationTestFixture, shouldResponseFor1to1to1RecurrentNetForVariousWeightsBeCorrect) {
    // recurrent example, neurons (1, 2, 3), 1 is input, 3 is output, 2 is hidden neuron, hidden neuron
    // takes recurrently response of the output
    // 1->2, 2->3, 3->2
    auto net = Net{ Net::InputSize{ 1 }, Net::OutputSize{ 1 } };
    const auto input = net.getNetInputs().front();
    auto hidden = net.addNeuron();
    auto output = net.getNetOutputs().front();
    const auto hiddenFromInput = Weight{ 0.5L };
    hidden->addInputs({ NeuronInput{ input, hiddenFromInput } });
    const auto outputFromHidden = Weight{ 0.25L };
    output->addInputs({ NeuronInput{ hidden, outputFromHidden } });
    const auto hiddenFromOutput = Weight{ 0.0625L };
    hidden->addInputs({ NeuronInput{ output, hiddenFromOutput } });

    const auto firstInputResponse = Neuron::activationFunction(
        netActivation * noScaling);
    const auto outputResponseAtTheStart = Response{ 0.0L };
    const auto firstHiddenResponse = Neuron::activationFunction(
        firstInputResponse * hiddenFromInput + outputResponseAtTheStart * hiddenFromOutput);
    const auto firstOutputResponse = Neuron::activationFunction(
        firstHiddenResponse * outputFromHidden);
    ASSERT_THAT(net.getNetResponseFor({ netActivation }), UnorderedElementsAre(firstOutputResponse));

    const auto secondInputResponse = firstInputResponse; // same netActivation
    const auto secondHiddenResponse = Neuron::activationFunction(
        secondInputResponse * hiddenFromInput + firstOutputResponse * hiddenFromOutput);
    const auto secondExpectedOutput = Neuron::activationFunction(secondHiddenResponse * outputFromHidden);
    ASSERT_THAT(net.getNetResponseFor({ NetActivation{inputValue} }), UnorderedElementsAre(secondExpectedOutput));
}

TEST_F(ForwardPropagationTestFixture, a) {

}
}