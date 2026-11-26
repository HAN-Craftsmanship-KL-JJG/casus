#include <drogon/HttpAppFramework.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <utility>

#include "convert.hpp"

namespace {

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

constexpr std::uint16_t port = 8080;
// A conversion blocks its thread, so use a few threads.
constexpr std::size_t threads = 4;

void fail(const Callback& callback, drogon::HttpStatusCode code, const std::string& reason) {
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setStatusCode(code);
    response->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    response->setBody(reason);
    callback(response);
}

// POST /convert/{format}: the body is Markdown, the answer is the file.
void convert(const drogon::HttpRequestPtr& request, Callback&& callback,
             const std::string& formatName) {
    // Drogon hands the callback over, so this function takes it over.
    const Callback respond = std::move(callback);
    const auto format = icde::parseFormat(formatName);
    if (!format.has_value()) {
        fail(respond, drogon::k400BadRequest, "Unknown format, use pdf or docx");
        return;
    }
    const auto file = icde::convert(*format, std::string{request->getBody()});
    if (!file.has_value()) {
        fail(respond, drogon::k500InternalServerError, "The conversion failed");
        return;
    }
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setContentTypeString(icde::contentType(*format));
    response->setBody(*file);
    respond(response);
}

} // namespace

int main() {
    drogon::app().registerHandler("/convert/{format}", &convert, {drogon::Post});

    drogon::app().setThreadNum(threads);
    // Only /tmp is writable in the container.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", port);
    drogon::app().run();
    return 0;
}
