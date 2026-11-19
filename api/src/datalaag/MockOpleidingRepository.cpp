#include "MockOpleidingRepository.hpp"

#include <iostream>

namespace icde::datalaag {

std::optional<domein::Opleiding> MockOpleidingRepository::zoek(const std::string& naam) const {
    std::cout << "datalaag: MockOpleidingRepository looks for " << naam << std::endl;
    if (naam == "HBO-ICT") {
        return domein::Opleiding{naam};
    }
    return std::nullopt;
}

}  // namespace icde::datalaag
