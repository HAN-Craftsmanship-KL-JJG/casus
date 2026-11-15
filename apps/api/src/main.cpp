#include <drogon/drogon.h>

#include <functional>

#include "status.hpp"

int main() {
    drogon::app().registerHandler(
        "/api/status",
        [](const drogon::HttpRequestPtr&,
           std::function<void(const drogon::HttpResponsePtr&)>&& callback) {
            callback(drogon::HttpResponse::newHttpJsonResponse(icde::makeStatus()));
        },
        {drogon::Get});

    // The container file system is read-only, only /tmp is writable.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().run();
    return 0;
}
