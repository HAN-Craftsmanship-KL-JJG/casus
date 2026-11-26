#include "status.hpp"

#include <iostream>

namespace icde::rest {

Json::Value makeStatus() {
    std::cout << "rest: makeStatus answers GET /api/status" << std::endl;
    Json::Value status;
    status["name"] = "icde-api";
    status["version"] = ICDE_VERSION;
    return status;
}

} // namespace icde::rest
