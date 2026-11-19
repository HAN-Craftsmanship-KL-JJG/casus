#include "PostgresOpleidingRepository.hpp"

#include <iostream>

namespace icde::datalaag {

std::optional<domein::Opleiding> PostgresOpleidingRepository::zoek(const std::string& naam) const {
    std::cout << "datalaag: PostgresOpleidingRepository looks for " << naam << std::endl;
    if (naam == "HBO-ICT") {
        return domein::Opleiding{naam};
    }
    return std::nullopt;
}

}  // namespace icde::datalaag
