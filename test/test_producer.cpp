#include <gtest/gtest.h>
#include <producer.h>
#include <iostream>

TEST(someshit, eloel1) {
    ASSERT_NO_THROW(producer{});
}

TEST(someshit, eloel2) {
    producer p{};
    ASSERT_NO_THROW(p.print_msg());
}