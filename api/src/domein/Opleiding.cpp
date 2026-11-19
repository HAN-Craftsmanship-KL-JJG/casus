#include "Opleiding.hpp"

#include <utility>

namespace icde::domein {

Opleiding::Opleiding(std::string naam) : naam_(std::move(naam)) {}

const std::string& Opleiding::naam() const {
    return naam_;
}

}  // namespace icde::domein
