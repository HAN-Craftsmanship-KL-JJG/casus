#include "OpleidingHandler.hpp"

#include <gtest/gtest.h>

#include "Opleiding.hpp"
#include "PostgresOpleidingRepository.hpp"

TEST(OpleidingHandlerTest, FindsAKnownOpleiding) {
    const icde::datalaag::PostgresOpleidingRepository opleidingen;
    const icde::applicatie::OpleidingHandler handler{opleidingen};

    const auto opleiding = handler.geefOpleiding("HBO-ICT");

    ASSERT_TRUE(opleiding.has_value());
    // value_or, because clang-tidy does not see that ASSERT_TRUE ends the test.
    EXPECT_EQ(opleiding.value_or(icde::domein::Opleiding{""}).naam(), "HBO-ICT");
}

TEST(OpleidingHandlerTest, FindsNoUnknownOpleiding) {
    const icde::datalaag::PostgresOpleidingRepository opleidingen;
    const icde::applicatie::OpleidingHandler handler{opleidingen};

    EXPECT_FALSE(handler.geefOpleiding("Onbekend").has_value());
}
