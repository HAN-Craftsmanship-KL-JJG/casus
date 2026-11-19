#include "status.hpp"

namespace icde::rest {

Json::Value makeStatus() {
    Json::Value status;
    status["name"] = "icde-api";
    status["version"] = ICDE_VERSION;
    return status;
}

}  // namespace icde::rest
