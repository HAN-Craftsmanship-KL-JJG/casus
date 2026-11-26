#pragma once

#include <optional>
#include <string>

#include "Opleiding.hpp"
#include "OpleidingRepository.hpp"

namespace icde::datalaag {

// The OpleidingRepository that reads PostgreSQL.
// For now it gives one fixed opleiding. #80 replaces this with a query.
class PostgresOpleidingRepository : public domein::OpleidingRepository {
public:
    [[nodiscard]] std::optional<domein::Opleiding> zoek(const std::string& naam) const override;
};

} // namespace icde::datalaag
