#pragma once

#include <string>

namespace icde::domein {

// Mock class: shows that the layers build together.
// The classes from the chapter Klassendiagram replace it.
class Opleiding {
public:
    explicit Opleiding(std::string naam);

    [[nodiscard]] const std::string& naam() const;

private:
    std::string naam_;
};

}  // namespace icde::domein
