#include "status.hpp"

namespace icde {

Json::Value makeStatus(const std::optional<std::string>& message) {
    Json::Value status;
    status["name"] = "icde-api";
    status["version"] = ICDE_VERSION;
    status["database"] = message.has_value() ? "ok" : "unavailable";
    if (message.has_value()) {
        status["message"] = *message;
    }
    return status;
}

}  // namespace icde
