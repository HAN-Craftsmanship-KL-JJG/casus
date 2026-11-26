#include <drogon/drogon.h>

#include <functional>
#include <string>

#include "convert.hpp"

namespace {

using Callback = std::function<void(const drogon::HttpResponsePtr&)>;

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
    const auto format = icde::parseFormat(formatName);
    if (!format.has_value()) {
        fail(callback, drogon::k400BadRequest, "Unknown format, use pdf or docx");
        return;
    }
    const auto file = icde::convert(*format, std::string{request->getBody()});
    if (!file.has_value()) {
        fail(callback, drogon::k500InternalServerError, "The conversion failed");
        return;
    }
    auto response = drogon::HttpResponse::newHttpResponse();
    response->setContentTypeString(icde::contentType(*format));
    response->setBody(*file);
    callback(response);
}

} // namespace

int main() {
    drogon::app().registerHandler("/convert/{format}", &convert, {drogon::Post});

    // A conversion blocks its thread, so use a few threads.
    drogon::app().setThreadNum(4);
    // Only /tmp is writable in the container.
    drogon::app().setUploadPath("/tmp/uploads");
    drogon::app().addListener("0.0.0.0", 8080);
    drogon::app().run();
    return 0;
}
