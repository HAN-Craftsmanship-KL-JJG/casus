#include "convert.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

namespace {

bool contains(const std::vector<std::string>& command, const std::string& argument) {
    return std::find(command.begin(), command.end(), argument) != command.end();
}

} // namespace

TEST(ConvertTest, ParsesTheTwoFormats) {
    EXPECT_EQ(icde::parseFormat("pdf"), icde::Format::Pdf);
    EXPECT_EQ(icde::parseFormat("docx"), icde::Format::Docx);
}

TEST(ConvertTest, RejectsAnUnknownFormat) {
    EXPECT_FALSE(icde::parseFormat("exe").has_value());
}

TEST(ConvertTest, UsesTypstOnlyForPdf) {
    const auto pdf = icde::pandocCommand(icde::Format::Pdf, "/tmp/in.md", "/tmp/out.pdf");
    const auto docx = icde::pandocCommand(icde::Format::Docx, "/tmp/in.md", "/tmp/out.docx");

    EXPECT_TRUE(contains(pdf, "--pdf-engine=typst"));
    EXPECT_FALSE(contains(docx, "--pdf-engine=typst"));
    EXPECT_TRUE(contains(docx, "--output=/tmp/out.docx"));
}
