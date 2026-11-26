#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace icde {

enum class Format { Pdf, Docx };

// "pdf" or "docx", empty for any other name.
std::optional<Format> parseFormat(const std::string& name);

std::string contentType(Format format);

// The Pandoc command that turns the Markdown file `input` into `output`.
std::vector<std::string> pandocCommand(Format format, const std::filesystem::path& input,
                                       const std::filesystem::path& output);

// Turns Markdown into a PDF or Word file with Pandoc. Empty when Pandoc fails.
std::optional<std::string> convert(Format format, const std::string& markdown);

} // namespace icde
