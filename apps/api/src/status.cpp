#include "status.hpp"

namespace icde {

Json::Value makeStatus() {
    Json::Value status;
    status["name"] = "icde-api";
    status["status"] = "ok";
    status["version"] = ICDE_VERSION;
    return status;
}

}  // namespace icde
