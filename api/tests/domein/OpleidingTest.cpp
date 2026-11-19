#include "Opleiding.hpp"

#include <gtest/gtest.h>

TEST(OpleidingTest, KeepsItsNaam) {
    const icde::domein::Opleiding opleiding{"HBO-ICT"};

    EXPECT_EQ(opleiding.naam(), "HBO-ICT");
}
