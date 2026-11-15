#pragma once

#include <json/value.h>

namespace icde {

// The answer of GET /api/status.
Json::Value makeStatus();

}  // namespace icde
