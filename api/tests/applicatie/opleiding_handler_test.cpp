#include "OpleidingHandler.hpp"

#include <gtest/gtest.h>

#include "MockOpleidingRepository.hpp"

TEST(OpleidingHandlerTest, FindsAKnownOpleiding) {
    const icde::datalaag::MockOpleidingRepository opleidingen;
    const icde::applicatie::OpleidingHandler handler{opleidingen};

    const auto opleiding = handler.geefOpleiding("HBO-ICT");

    ASSERT_TRUE(opleiding.has_value());
    EXPECT_EQ(opleiding->naam(), "HBO-ICT");
}

TEST(OpleidingHandlerTest, FindsNoUnknownOpleiding) {
    const icde::datalaag::MockOpleidingRepository opleidingen;
    const icde::applicatie::OpleidingHandler handler{opleidingen};

    EXPECT_FALSE(handler.geefOpleiding("Onbekend").has_value());
}
