#include "Opleiding.hpp"

#include <iostream>
#include <string>
#include <utility>

namespace icde::domein {

Opleiding::Opleiding(std::string naam) : naam_(std::move(naam)) {
    std::cout << "domein: Opleiding " << naam_ << " is created" << '\n' << std::flush;
}

const std::string& Opleiding::naam() const {
    return naam_;
}

} // namespace icde::domein
