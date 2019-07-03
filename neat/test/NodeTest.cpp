#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gsl/gsl>
#include "neat/src/Node.hpp"

namespace spacey::neat {
using ::testing::UnorderedElementsAre;

TEST(SimpleInstanciate, shouldInstantieatedNodeSetParamsProperly) {
    Node node{};
    node.addOutputNode(gsl::not_null(&node));
    EXPECT_THAT(node.getOutputNodes(), UnorderedElementsAre(gsl::not_null(&node)));
}

}