#include <drogon/drogon.h>

#include <functional>
#include <iostream>

#include "OpleidingHandler.hpp"
#include "PostgresOpleidingRepository.hpp"
#include "status.hpp"

namespace {

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

void status(const drogon::HttpRequestPtr&, Callback&& callback) {
    callback(drogon::HttpResponse::newHttpJsonResponse(icde::rest::makeStatus()));
}

} // namespace

// The only file that knows both rest and datalaag.
// Here the use cases will create the repositories and hand them to the handlers.
int main() {
    drogon::app().registerHandler("/api/status", &status, {drogon::Get});

    // Mock: one call through the layers at startup, so the log shows them work together.
    const icde::datalaag::PostgresOpleidingRepository opleidingen;
    const icde::applicatie::OpleidingHandler handler{opleidingen};
    if (const auto opleiding = handler.geefOpleiding("HBO-ICT")) {
        std::cout << "main: found Opleiding " << opleiding->naam() << std::endl;
    }

    // Only /tmp is writable in the container.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().run();
    return 0;
}
