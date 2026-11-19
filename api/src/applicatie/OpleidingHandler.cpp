#include "OpleidingHandler.hpp"

#include <iostream>

namespace icde::applicatie {

OpleidingHandler::OpleidingHandler(const domein::OpleidingRepository& opleidingen)
    : opleidingen_(opleidingen) {}

std::optional<domein::Opleiding> OpleidingHandler::geefOpleiding(const std::string& naam) const {
    std::cout << "applicatie: OpleidingHandler asks the repository for " << naam << std::endl;
    return opleidingen_.zoek(naam);
}

}  // namespace icde::applicatie
