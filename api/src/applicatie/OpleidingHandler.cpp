#include "OpleidingHandler.hpp"

namespace icde::applicatie {

OpleidingHandler::OpleidingHandler(const domein::OpleidingRepository& opleidingen)
    : opleidingen_(opleidingen) {}

std::optional<domein::Opleiding> OpleidingHandler::geefOpleiding(const std::string& naam) const {
    return opleidingen_.zoek(naam);
}

}  // namespace icde::applicatie
