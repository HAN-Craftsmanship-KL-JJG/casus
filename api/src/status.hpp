#pragma once

#include <json/value.h>

#include <optional>
#include <string>

namespace icde {

// The answer of GET /api/status.
// `message` is empty when the database gives no answer.
Json::Value makeStatus(const std::optional<std::string>& message);

}  // namespace icde
