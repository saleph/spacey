#include <gtest/gtest.h>
#include <iostream>
#include "../include/producer.hpp"

TEST(someshit, eloel1) {
    ASSERT_NO_THROW(producer{});
}

TEST(someshit, eloel2) {
    producer p{};
    ASSERT_NO_THROW(p.print_msg());
}