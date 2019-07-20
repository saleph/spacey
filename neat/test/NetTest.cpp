#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gsl/gsl>
#include <neat/src/Net.hpp>

namespace spacey::neat {
using ::testing::UnorderedElementsAre;

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
}