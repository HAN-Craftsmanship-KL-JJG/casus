#include <drogon/drogon.h>

#include <functional>

#include "status.hpp"

namespace {

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

void status(const drogon::HttpRequestPtr&, Callback&& callback) {
    callback(drogon::HttpResponse::newHttpJsonResponse(icde::rest::makeStatus()));
}

}  // namespace

// The only file that knows both rest and datalaag.
// Here the use cases will create the repositories and hand them to the handlers.
int main() {
    drogon::app().registerHandler("/api/status", &status, {drogon::Get});

    // Only /tmp is writable in the container.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().run();
    return 0;
}
