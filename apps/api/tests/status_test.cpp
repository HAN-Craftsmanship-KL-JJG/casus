#include "status.hpp"

#include <gtest/gtest.h>

TEST(StatusTest, ReportsOk) {
    const Json::Value status = icde::makeStatus();

    EXPECT_EQ(status["status"].asString(), "ok");
    EXPECT_EQ(status["name"].asString(), "icde-api");
}

TEST(StatusTest, ReportsTheProjectVersion) {
    EXPECT_EQ(icde::makeStatus()["version"].asString(), "0.1.0");
}
