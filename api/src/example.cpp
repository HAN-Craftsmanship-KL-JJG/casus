#include "example.hpp"

namespace icde {

std::string exampleMarkdown(const std::string& message) {
    return "# ICDE\n\nDit document komt van de documentserver.\n\n"
           "Bericht uit de database: " +
           message + "\n";
}

}  // namespace icde
