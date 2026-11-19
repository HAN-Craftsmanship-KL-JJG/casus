#pragma once

#include <optional>
#include <string>

#include "Opleiding.hpp"

namespace icde::domein {

// The domein owns this interface, and the datalaag implements it.
// So the datalaag depends on the domein, not the other way round.
class OpleidingRepository {
public:
    OpleidingRepository() = default;
    OpleidingRepository(const OpleidingRepository&) = delete;
    OpleidingRepository& operator=(const OpleidingRepository&) = delete;
    OpleidingRepository(OpleidingRepository&&) = delete;
    OpleidingRepository& operator=(OpleidingRepository&&) = delete;
    virtual ~OpleidingRepository() = default;

    // Empty when no opleiding has this naam.
    [[nodiscard]] virtual std::optional<Opleiding> zoek(const std::string& naam) const = 0;
};

}  // namespace icde::domein
