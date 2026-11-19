#include "Status.hpp"

#include <gtest/gtest.h>

TEST(StatusTest, ReportsNameAndVersion) {
    const Json::Value status = icde::rest::makeStatus();

    EXPECT_EQ(status["name"].asString(), "icde-api");
    EXPECT_EQ(status["version"].asString(), "0.0.1");
}
