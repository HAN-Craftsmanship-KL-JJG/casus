#include "example.hpp"

#include <gtest/gtest.h>

TEST(ExampleTest, PutsTheMessageInTheDocument) {
    const std::string markdown = icde::exampleMarkdown("hallo");

    EXPECT_NE(markdown.find("# ICDE"), std::string::npos);
    EXPECT_NE(markdown.find("Bericht uit de database: hallo"), std::string::npos);
}
