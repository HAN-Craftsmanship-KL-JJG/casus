#pragma once

#include <json/value.h>

namespace icde::rest {

// The answer of GET /api/status.
Json::Value makeStatus();

}  // namespace icde::rest
