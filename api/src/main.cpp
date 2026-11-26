#include <drogon/HttpAppFramework.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>

#include <cstdint>
#include <functional>
#include <iostream>
#include <utility>

#include "OpleidingHandler.hpp"
#include "PostgresOpleidingRepository.hpp"
#include "status.hpp"

namespace {

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

constexpr std::uint16_t port = 8080;

void status(const drogon::HttpRequestPtr& /*request*/, Callback&& callback) {
    // Drogon hands the callback over, so this function takes it over.
    const Callback respond = std::move(callback);
    respond(drogon::HttpResponse::newHttpJsonResponse(icde::rest::makeStatus()));
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
        std::cout << "main: found Opleiding " << opleiding->naam() << '\n' << std::flush;
    }

    // Only /tmp is writable in the container.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", port);
    drogon::app().run();
    return 0;
}
