#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "neat/src/Node.hpp"

namespace spacey::neat {
using ::testing::UnorderedElementsAre;

TEST(SimpleInstanciate, shouldInstantieatedNodeSetParamsProperly) {
    Node node{};
    node.addOutputNode(&node);
    EXPECT_THAT(node.getOutputNodes(), UnorderedElementsAre(nullptr_t));
}

}