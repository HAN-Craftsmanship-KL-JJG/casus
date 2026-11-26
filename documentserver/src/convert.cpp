#include "convert.hpp"

#include <spawn.h>
// POSIX mkdtemp and WIFEXITED, which <cstdlib> does not promise.
#include <stdlib.h> // NOLINT(modernize-deprecated-headers)
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <ios>
#include <iterator>
#include <optional>
#include <string>
#include <vector>

namespace icde {

namespace {

// No shell, so text from a request never becomes a command.
// A copy of the command, because posix_spawnp wants text it may change.
bool run(std::vector<std::string> command) {
    std::vector<char*> arguments;
    arguments.reserve(command.size() + 1);
    for (std::string& argument : command) {
        arguments.push_back(argument.data());
    }
    arguments.push_back(nullptr);

    pid_t process = 0;
    if (posix_spawnp(&process, arguments[0], nullptr, nullptr, arguments.data(), environ) != 0) {
        return false;
    }
    int status = 0;
    return waitpid(process, &status, 0) == process && WIFEXITED(status) && WEXITSTATUS(status) == 0;
}

} // namespace

std::optional<Format> parseFormat(const std::string& name) {
    if (name == "pdf") {
        return Format::Pdf;
    }
    if (name == "docx") {
        return Format::Docx;
    }
    return std::nullopt;
}

std::string contentType(Format format) {
    return format == Format::Pdf
               ? "application/pdf"
               : "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
}

std::vector<std::string> pandocCommand(Format format, const std::filesystem::path& input,
                                       const std::filesystem::path& output) {
    std::vector<std::string> command{"pandoc", "--from=markdown", input.string(),
                                     "--output=" + output.string()};
    if (format == Format::Pdf) {
        command.emplace_back("--pdf-engine=typst");
    }
    return command;
}

std::optional<std::string> convert(Format format, const std::string& markdown) {
    std::string pattern = (std::filesystem::temp_directory_path() / "convert-XXXXXX").string();
    if (mkdtemp(pattern.data()) == nullptr) {
        return std::nullopt;
    }
    const std::filesystem::path directory{pattern};
    const std::filesystem::path input = directory / "input.md";
    const std::filesystem::path output =
        directory / (format == Format::Pdf ? "output.pdf" : "output.docx");

    std::ofstream{input, std::ios::binary} << markdown;

    std::optional<std::string> result;
    if (run(pandocCommand(format, input, output))) {
        std::ifstream file{output, std::ios::binary};
        result = std::string{std::istreambuf_iterator<char>{file}, {}};
    }
    std::filesystem::remove_all(directory);
    return result;
}

} // namespace icde
