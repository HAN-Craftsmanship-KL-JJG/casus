#pragma once

#include <optional>
#include <string>

#include "Opleiding.hpp"
#include "OpleidingRepository.hpp"

namespace icde::datalaag {

// Mock repository with one fixed opleiding instead of a database.
// A repository that uses PostgreSQL replaces it.
class MockOpleidingRepository : public domein::OpleidingRepository {
public:
    [[nodiscard]] std::optional<domein::Opleiding> zoek(const std::string& naam) const override;
};

}  // namespace icde::datalaag
