#include "MockOpleidingRepository.hpp"

namespace icde::datalaag {

std::optional<domein::Opleiding> MockOpleidingRepository::zoek(const std::string& naam) const {
    if (naam == "HBO-ICT") {
        return domein::Opleiding{naam};
    }
    return std::nullopt;
}

}  // namespace icde::datalaag
