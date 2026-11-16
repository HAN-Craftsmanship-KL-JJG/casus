#include <drogon/drogon.h>

#include <cstdlib>
#include <functional>
#include <optional>
#include <string>

#include "example.hpp"
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

// Passes the file of the document server on to the browser.
void sendDocument(const Callback& callback, const std::string& format,
                  const std::string& markdown) {
    auto request = drogon::HttpRequest::newHttpRequest();
    request->setMethod(drogon::Post);
    request->setPath("/convert/" + format);
    request->setContentTypeString("text/markdown");
    request->setBody(markdown);

    auto client = drogon::HttpClient::newHttpClient(
        env("DOCUMENTSERVER_URL", "http://localhost:8081"));
    client->sendRequest(
        request,
        [callback, format, client](drogon::ReqResult result,
                                   const drogon::HttpResponsePtr& answer) {
            auto response = drogon::HttpResponse::newHttpResponse();
            if (result != drogon::ReqResult::Ok || answer->getStatusCode() != drogon::k200OK) {
                // The document server gave no file.
                response->setStatusCode(drogon::k502BadGateway);
                callback(response);
                return;
            }
            response->setContentTypeString(answer->getHeader("content-type"));
            response->addHeader("Content-Disposition",
                                "attachment; filename=\"voorbeeld." + format + "\"");
            response->setBody(std::string{answer->getBody()});
            callback(response);
        },
        30.0);
}

// GET /api/example/{format}: the row from the database as a PDF or Word file.
void example(const drogon::HttpRequestPtr&, Callback&& callback, const std::string& format) {
    if (format != "pdf" && format != "docx") {
        callback(drogon::HttpResponse::newNotFoundResponse());
        return;
    }
    drogon::app().getDbClient()->execSqlAsync(
        "SELECT message FROM example ORDER BY id LIMIT 1",
        [callback, format](const drogon::orm::Result& rows) {
            const std::string message =
                rows.empty() ? std::string{} : rows[0]["message"].as<std::string>();
            sendDocument(callback, format, icde::exampleMarkdown(message));
        },
        [callback](const drogon::orm::DrogonDbException& error) {
            LOG_ERROR << "Database query failed: " << error.base().what();
            respond(callback, std::nullopt);
        });
}

}  // namespace

int main() {
    drogon::app().registerHandler("/api/status", &status, {drogon::Get});
    drogon::app().registerHandler("/api/example/{format}", &example, {drogon::Get});

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

    // Only /tmp is writable in the container.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().run();
    return 0;
}
