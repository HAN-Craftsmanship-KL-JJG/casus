#include "PostgresOpleidingRepository.hpp"

#include <iostream>
#include <optional>
#include <string>

#include "Opleiding.hpp"

namespace icde::datalaag {

std::optional<domein::Opleiding> PostgresOpleidingRepository::zoek(const std::string& naam) const {
    std::cout << "datalaag: PostgresOpleidingRepository looks for " << naam << '\n' << std::flush;
    if (naam == "HBO-ICT") {
        return domein::Opleiding{naam};
    }
    return std::nullopt;
}

} // namespace icde::datalaag
