#include "status.hpp"

#include <gtest/gtest.h>

#include <optional>
#include <string>

TEST(StatusTest, ReportsNameAndVersion) {
    const Json::Value status = icde::makeStatus(std::nullopt);

    EXPECT_EQ(status["name"].asString(), "icde-api");
    EXPECT_EQ(status["version"].asString(), "0.1.0");
}

TEST(StatusTest, ReportsTheMessageFromTheDatabase) {
    const Json::Value status = icde::makeStatus(std::string{"hallo"});

    EXPECT_EQ(status["database"].asString(), "ok");
    EXPECT_EQ(status["message"].asString(), "hallo");
}

TEST(StatusTest, ReportsAnUnavailableDatabase) {
    const Json::Value status = icde::makeStatus(std::nullopt);

    EXPECT_EQ(status["database"].asString(), "unavailable");
    EXPECT_FALSE(status.isMember("message"));
}
