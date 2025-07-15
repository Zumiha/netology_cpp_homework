#pragma once

#include <string>
#include <chrono>
#include <optional>
#include "UrlParser.h"

class HTTPUtils {
public:
    struct Config {
        std::chrono::seconds timeout{30};
        std::string userAgent{"HTTPUtils/1.0"};
        bool verifySSL{false};
        bool textOnly{true};
    };

    static std::optional<std::string> fetchPage(const Link& url, const Config& config);
    
private:
    static bool isTextContent(const std::string& content);
};