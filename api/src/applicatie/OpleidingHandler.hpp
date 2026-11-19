#pragma once

#include <optional>
#include <string>

#include "Opleiding.hpp"
#include "OpleidingRepository.hpp"

namespace icde::applicatie {

// Mock handler: shows that the applicatie uses the domein only through its interfaces.
// The handlers from the chapter Klassendiagram replace it.
class OpleidingHandler {
public:
    explicit OpleidingHandler(const domein::OpleidingRepository& opleidingen);

    [[nodiscard]] std::optional<domein::Opleiding> geefOpleiding(const std::string& naam) const;

private:
    const domein::OpleidingRepository& opleidingen_;
};

}  // namespace icde::applicatie
