#include <drogon/drogon.h>

#include <cstdlib>
#include <functional>
#include <optional>
#include <string>

#include "status.hpp"

namespace {

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

std::string env(const char* name, const std::string& fallback) {
    const char* value = std::getenv(name);
    return value != nullptr ? value : fallback;
}

void respond(const Callback& callback, const std::optional<std::string>& message) {
    auto response = drogon::HttpResponse::newHttpJsonResponse(icde::makeStatus(message));
    if (!message.has_value()) {
        response->setStatusCode(drogon::k503ServiceUnavailable);
    }
    callback(response);
}

void status(const drogon::HttpRequestPtr&, Callback&& callback) {
    drogon::app().getDbClient()->execSqlAsync(
        "SELECT message FROM example ORDER BY id LIMIT 1",
        [callback](const drogon::orm::Result& rows) {
            respond(callback, rows.empty() ? std::string{} : rows[0]["message"].as<std::string>());
        },
        [callback](const drogon::orm::DrogonDbException& error) {
            LOG_ERROR << "Database query failed: " << error.base().what();
            respond(callback, std::nullopt);
        });
}

}  // namespace

int main() {
    drogon::app().registerHandler("/api/status", &status, {drogon::Get});

    drogon::orm::PostgresConfig database{};
    database.host = env("DB_HOST", "localhost");
    database.port = 5432;
    database.databaseName = env("DB_NAME", "icde");
    database.username = env("DB_USER", "icde");
    database.password = env("DB_PASSWORD", "icde");
    database.connectionNumber = 2;
    database.name = "default";
    database.timeout = 5.0;  // Seconds per query.
    drogon::app().addDbClient(database);

    // The container file system is read-only, only /tmp is writable.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().run();
    return 0;
}
