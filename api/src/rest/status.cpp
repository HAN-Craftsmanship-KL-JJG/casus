#include "status.hpp"

#include <json/value.h>

#include <iostream>

namespace icde::rest {

Json::Value makeStatus() {
    std::cout << "rest: makeStatus answers GET /api/status" << '\n' << std::flush;
    Json::Value status;
    status["name"] = "icde-api";
    status["version"] = ICDE_VERSION;
    return status;
}

} // namespace icde::rest
