#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gsl/gsl>
#include <neat/src/Net.hpp>

namespace spacey::neat {
using ::testing::UnorderedElementsAre;
using ::testing::UnorderedElementsAreArray;

class NetTestFixture : public ::testing::Test {
public:
    void TearDown() override {
        net = Net{ Net::InputSize{defaultInputSize}, Net::OutputSize{defaultOutputSize} };
    }

    const std::size_t defaultInputSize{ 5 };
    const std::size_t defaultOutputSize{ 6 };
    Net net{ Net::InputSize{defaultInputSize}, Net::OutputSize{defaultOutputSize} };
    const Weight defaultWeight{ 1.0L };
    const Weight noScaling{ defaultWeight };
    const long double inputValue = 10.0L;
};

TEST_F(NetTestFixture, shouldThrowWhenInputSizeIsZero) {
    ASSERT_THROW(Net(Net::InputSize{ 0 }, Net::OutputSize{ defaultOutputSize }), gsl::fail_fast);
}

TEST_F(NetTestFixture, shouldThrowWhenOutputSizeIsZero) {
    ASSERT_THROW(Net(Net::InputSize{ defaultInputSize }, Net::OutputSize{ 0 }), gsl::fail_fast);
}

TEST_F(NetTestFixture, shouldThrowWhenInputAndOutputSizeAreZero) {
    ASSERT_THROW(Net(Net::InputSize{ 0 }, Net::OutputSize{ 0 }), gsl::fail_fast);
}

TEST_F(NetTestFixture, shouldNetInputsSizeMatchDeclaredOneDuringConstruction) {
    ASSERT_EQ(net.getNetInputs().size(), defaultInputSize);
}

TEST_F(NetTestFixture, shouldNetOutputsSizeMatchDeclaredOneDuringConstruction) {
    ASSERT_EQ(net.getNetOutputs().size(), defaultOutputSize);
}

TEST_F(NetTestFixture, shouldOutputDirectlyConnectedToInputWithoutScallingReturnSameValueAsResponse) {
    auto net = Net{ Net::InputSize{ 1 }, Net::OutputSize{ 1 } };
    const auto input = net.getNetInputs().front();
    auto output = net.getNetOutputs().front();
    output->addInputs({ NeuronInput{input, noScaling} });

    const auto inputResponse = Neuron::activationFunction({ inputValue });
    const auto expectedOutput = Neuron::activationFunction(inputResponse * noScaling);
    ASSERT_THAT(net.getNetResponseFor({ NetInput{inputValue} }), UnorderedElementsAre(expectedOutput));
}

TEST_F(NetTestFixture, a) {

}
}